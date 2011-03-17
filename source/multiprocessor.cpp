/**
 * MULTIPROCESSOR 
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <pthread.h>
#include "processlist.hpp"
#include "loader.hpp"
#include "memory.hpp"
#include "number.hpp"
#include "instruction.hpp"
#include "dispatcher.hpp"
#include "stscheduler.hpp"
#include "ltscheduler.hpp"
#include "loadbalancer.hpp"
#include "pcb.hpp"
#include "cpu.hpp"

using namespace std;

/**
 * OPTIONS.
 */
const unsigned int NUM_THREADS = 4;
const bool DEBUGGING = true;

/**
 * Globals.
 */
Memory* disk = 0;
Memory* ram = 0;
ProcessList* globalProcList = 0;
LongTermScheduler* lts = 0;
pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t interrupt = PTHREAD_COND_INITIALIZER;
vector<pthread_t> cpuThreads;
vector<Cpu*> cpus;

/**
 * CPU Thread 
 * Runs the CPU.
 */
void* cpu_thread(void*)
{
	Cpu* cpu = 0;
	ShortTermScheduler* sts = 0;
	Dispatcher* dsp = 0;
	LoadBalancer* bal = 0;
	ProcessList* pList = 0;
	bool done = false;
	int ltsCnt = 0; // TODO: Global?

	// Thread-specific instances
	cpu = new Cpu(ram);
	bal = new LoadBalancer(cpu, globalProcList);
	sts = new ShortTermScheduler(cpu);
	dsp = new Dispatcher(cpu, ram);

	if(DEBUGGING) {
		cpu->setDebug(true);
		bal->setDebug(true);
		sts->setDebug(true);
		dsp->setDebug(true);
	}

	pList = cpu->getProcessList();

	// Run the schedulers once at the start
	bal->importNewProcess();
	sts->rebuildQueue();
	dsp->dispatch();
	ltsCnt++;

	// TODO TODO: Locking, signalling...
	do 
	{
		done = true;

		//cout << "CPU " << cpu->getId() << " ITER\n"; // XXX DEBUG

		// TODO/XXX -- temporary until integrated elsewhere:
		if(cpu->getPcb()) {
			cpu->getPcb()->runTime.start();
		}

		// CPU (non-interruptible)
		// Note: It may not have a process at this point. 
		while(!cpu->isComplete()) {
			//cout << "CPU " << cpu->getId() << " EXECUTING\n"; // XXX DEBUG
			cpu->execute();
		}

		// TODO/XXX -- temporary until integrated elsewhere:
		if(cpu->getPcb()) {
			cpu->getPcb()->runTime.end();
		}

		//cout << "LTS COUNTER: " << ltsCnt << endl; // XXX DEBUG

		// LTS only runs every so often.
		// TODO: Make count global?
		if(ltsCnt % 4 == 0) {
			lts->schedule();
		}
		ltsCnt++;

		/*cout << "CPU " << cpu->getId() << " #READY = "; // XXX DEBUG
		pList->printReady();
		cout << "CPU " << cpu->getId() << " #UNREADY = "; // XXX DEBUG
		pList->printUnready();*/

		// Balancer, STS, Dispatch
		bal->importNewProcess();
		sts->rebuildQueue();
		dsp->dispatch();

		// See if we can stop the CPU.
		for(unsigned int i = 0; i < globalProcList->all.size(); i++) {
			if(globalProcList->all[i]->state != STATE_TERM_UNLOADED) {
				done = false;
				break;
			}
		}
	} 
	while(!done);

	if(DEBUGGING) {
		cout << "CPU THREAD " << cpu->getId() << " DONE\n";
	}

	return 0;
}

/**
 * Main func
 */
int main(int argc, char *argv[])
{
	Loader loader;
	pthread_t cpuThread;

	disk = new Memory(2048);
	ram = new Memory(1024);

	loader = Loader("data/datafile2.txt");
	globalProcList = loader.loadDisk(disk);

	lts = new LongTermScheduler(disk, ram, globalProcList, SCHEDULE_RAM_FCFS);

	if(DEBUGGING) {
		lts->setDebug(true);
	}

	// Run LTS once at start
	lts->schedule();

	// Spawn CPU threads. 
	// CPU Threads are Symmetric Processing units (self-scheduling, etc.)
	for(unsigned int i = 0; i < NUM_THREADS; i++)
	{
		cout << "Spawning CPU Thread...\n";
		pthread_create(&cpuThread, 0, &cpu_thread, 0);
		cpuThreads.push_back(cpuThread);
	}

	// Join all CPU threads
	for(unsigned int i = 0; i < cpuThreads.size(); i++) {
		pthread_join(cpuThreads[i], 0);
	}

	// Final Report
	cout << "\nFinal PCB Values:\n";
	cout << "=================\n";
	globalProcList->printJobs();
	cout << endl;

	cout << "Writing memories to disk... (ram.txt, disk.txt)\n";
	ram->writeDisk("ram.txt");
	disk->writeDisk("disk.txt");

	return 0;	
}

