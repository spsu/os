/**
 * UNIPROCESSOR
 */

#include <iostream>
#include <sstream>
#include "accounting.hpp"
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
 * Print All PCBs
 * 	Debugging facility
 */
/*void print_pcbs(PcbList& pcbs) {
	for(unsigned int i = 0; i < pcbs.size(); i++)
		cout << pcbs.at(i)->toString() << endl;
}*/

Cpu* cpu = 0;
Memory* disk = 0;
Memory* ram = 0;

void run_jobs() 
{
	ProcessList* pList = 0;
	Pcb* pcb = 0;
	LongTermScheduler* lts = 0;
	ShortTermScheduler* sts = 0;
	Dispatcher* dsp = 0;
	bool done = false;

	pList = cpu->getProcessList();

	lts = new LongTermScheduler(disk, ram, pList); // TODO: CPU instead of pList
	sts = new ShortTermScheduler(cpu);
	dsp = new Dispatcher(cpu, ram, pList);

	while(!done)
	{
		bool canStop = true;

		lts->schedule();

		cout << "Disk, Ram: ";
		cout << disk->numAllocated() << ", ";
		cout << ram->numAllocated() << endl;

		sts->rebuildQueue();
		dsp->dispatch();

		while(!cpu->isComplete()) {
			cpu->execute();
		}

		cpu->printRegs();

		for(unsigned int i = 0; i < pList->all.size(); i++) {
			if(pList->all[i]->state != STATE_TERM_UNLOADED) {
				canStop = false;
				break;
			}
		}

		if(canStop) {
			done = true;
		}
	}

	/*for(unsigned int i = 0; i < pList->all.size(); i++) 
	{
		pcb = pList->all.at(i);
		cout << "Process " << i << ": ";
		cout << cpu->getReg(0) << "\t";
		cout << cpu->readCount << "\t" << cpu->writeCount; 
		cout << endl;
	}*/
}

/**
 * Main func
 */
int main(int argc, char *argv[])
{
	Loader loader;
	ProcessList* pList = 0;

	loader = Loader("data/datafile2.txt");
	disk = new Memory(2048);
	ram = new Memory(1024);

	pList = loader.loadDisk(disk);
	cpu = new Cpu(ram, pList);
	
	// XXX: DEBUG
	run_jobs();

	return 0;	
}

