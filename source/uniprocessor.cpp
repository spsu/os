/**
 * UNIPROCESSOR
 */

#include <iostream>
#include <sstream>
#include <pthread.h>
#include "processlist.hpp"
#include "loader.hpp"
#include "memory.hpp"
#include "number.hpp"
#include "instruction.hpp"
#include "dispatcher.hpp"
#include "stscheduler.hpp"
#include "ltscheduler.hpp"
#include "pcb.hpp"
#include "cpu.hpp"

using namespace std;

/**
 * Globals.
 */
Cpu* cpu = 0;
Memory* disk = 0;
Memory* ram = 0;
pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t interrupt = PTHREAD_COND_INITIALIZER;

/**
 * CPU Thread 
 * Runs the CPU.
 */
void* cpu_thread(void*)
{
	ProcessList* pList = 0;
	bool done = false;

	pList = cpu->getProcessList();

	do 
	{
		done = true;
		pthread_mutex_lock(&mux);

		// CPU (non-interruptible)
		// Note: It may not have a process at this point. 
		while(!cpu->isComplete()) {
			cpu->execute();
		}

		// Signal job complete (or interrupt: TODO)
		pthread_cond_signal(&interrupt);
		pthread_mutex_unlock(&mux);
		
		// See if we can stop the CPU.
		for(unsigned int i = 0; i < pList->all.size(); i++) {
			if(pList->all[i]->state != STATE_TERM_UNLOADED) {
				done = false;
				break;
			}
		}

	} 
	while(!done);

	return 0;
}

/**
 * Driver Thread
 * Runs the schedulers and dispatcher.
 */
void* driver_thread(void*) 
{
	Loader loader;
	ProcessList* pList = 0;
	LongTermScheduler* lts = 0;
	ShortTermScheduler* sts = 0;
	Dispatcher* dsp = 0;
	pthread_t cpuThread;
	bool done = false;
	unsigned int ltsCnt = 0;

	disk = new Memory(2048);
	ram = new Memory(1024);

	loader = Loader("data/datafile2.txt");
	pList = loader.loadDisk(disk);

	cpu = new Cpu(ram, pList);

	lts = new LongTermScheduler(disk, ram, pList); // TODO: CPU instead of pList?
	sts = new ShortTermScheduler(cpu);
	dsp = new Dispatcher(cpu, ram);

	// Run the schedulers once at the start
	lts->schedule();
	sts->rebuildQueue();
	dsp->dispatch();
	ltsCnt = 1;

	// Spawn CPU thread. 
	pthread_create(&cpuThread, 0, &cpu_thread, 0);

	do
	{
		done = true;

		// Wait for interrupt. 
		pthread_mutex_lock(&mux);
		pthread_cond_wait(&interrupt, &mux);

		// LTS only runs every so often.
		if(ltsCnt % 4 == 0) {
			lts->schedule();
		}
		ltsCnt++;

		// STS, Dispatcher
		sts->rebuildQueue();
		dsp->dispatch();

		// See if we can stop. 
		for(unsigned int i = 0; i < pList->all.size(); i++) {
			if(pList->all[i]->state != STATE_TERM_UNLOADED) {
				done = false;
				break;
			}
		}

		pthread_mutex_unlock(&mux);
	} 
	while(!done);

	pthread_join(cpuThread, 0);

	// Final Report
	cout << "\nFinal PCB Values:\n";
	cout << "=================\n";
	pList->printJobs();
	cout << endl;

	cout << "Writing memories to disk...\n";
	ram->writeDisk("ram.txt");
	disk->writeDisk("disk.txt");

	return 0;
}

/**
 * Main func
 */
int main(int argc, char *argv[])
{
	pthread_t driverThread;

	// Create and join driver thread
	pthread_create(&driverThread, 0, &driver_thread, 0);
	pthread_join(driverThread, 0);

	return 0;	
}

