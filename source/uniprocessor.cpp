/**
 * UNIPROCESSOR
 */

#include <iostream>
#include <sstream>
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

/**
 * Run Jobs
 */
void run_jobs() 
{
	ProcessList* pList = 0;
	LongTermScheduler* lts = 0;
	ShortTermScheduler* sts = 0;
	Dispatcher* dsp = 0;

	bool done = false;
	unsigned int ltsCnt = 0;

	pList = cpu->getProcessList();

	lts = new LongTermScheduler(disk, ram, pList); // TODO: CPU instead of pList?
	sts = new ShortTermScheduler(cpu);
	dsp = new Dispatcher(cpu, ram);

	// Run the LTS once at the start
	lts->schedule();
	ltsCnt = 1;

	do
	{
		done = true;

		// LTS only runs every so often.
		if(ltsCnt % 4 == 0) {
			lts->schedule();
		}
		ltsCnt++;

		// STS, Dispatcher
		sts->rebuildQueue();
		dsp->dispatch();

		// CPU (non-interruptible)
		while(!cpu->isComplete()) {
			cpu->execute();
		}

		// See if we can stop. 
		for(unsigned int i = 0; i < pList->all.size(); i++) {
			if(pList->all[i]->state != STATE_TERM_UNLOADED) {
				done = false;
				break;
			}
		}
	} while(!done);
}

/**
 * Main func
 */
int main(int argc, char *argv[])
{
	Loader loader;
	ProcessList* pList = 0;

	disk = new Memory(2048);
	ram = new Memory(1024);

	loader = Loader("data/datafile2.txt");
	pList = loader.loadDisk(disk);

	cpu = new Cpu(ram, pList);

	// Run Jobs
	run_jobs();

	// Final Report
	cout << "\nFinal PCB Values:\n";
	cout << "=================\n";
	pList->printJobs();
	cout << endl;

	cout << "Writing memories to disk...\n\n";
	ram->writeDisk("ram.txt");
	disk->writeDisk("disk.txt");

	return 0;	
}

