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
 * Globals.
 */
Cpu* cpu = 0;
Memory* disk = 0;
Memory* ram = 0;

/**
 * Print All PCBs
 * A debugging facility
 */
void print_jobs(ProcessList* pcbs) {
	for(unsigned int i = 0; i < pcbs->all.size(); i++)
		cout << pcbs->all[i]->toString() << endl;
}

void print_job_states(ProcessList* pcbs) {
	for(unsigned int i = 0; i < pcbs->all.size(); i++) {
		cout << "PCB[";
		cout << pcbs->all[i]->id << "]: ";
		cout << pcbs->all[i]->stateStr() << ",  ";
	}
}

void print_ready_jobs(ProcessList* pcbs) {
	cout << "Ready: ";
	for(unsigned int i = 0; i < pcbs->all.size(); i++) {
		if(pcbs->all[i]->state == STATE_READY) {
			cout << pcbs->all[i]->id << ", ";
		}
	}
}



/**
 * Run Jobs
 */
void run_jobs() 
{
	ProcessList* pList = 0;
	Pcb* pcb = 0;
	LongTermScheduler* lts = 0;
	ShortTermScheduler* sts = 0;
	Dispatcher* dsp = 0;
	bool done = false;
	unsigned int count = 0;

	pList = cpu->getProcessList();

	lts = new LongTermScheduler(disk, ram, pList); // TODO: CPU instead of pList
	sts = new ShortTermScheduler(cpu);
	dsp = new Dispatcher(cpu, ram);

	// XXX XXX DEBUG
	//cout << "=== ALL JOBS ===\n";
	//print_jobs(pList);
	//print_job_states(pList);
	//cout << endl;

	while(!done)
	{
		bool canStop = true;

		cout << "=== CPU CYCLE " << count;
		cout << " BEGIN ===\n";
		count++;

		cout << "Disk, Ram: ";
		cout << disk->numAllocated() << ", ";
		cout << ram->numAllocated() << endl;

		lts->schedule();

		sts->rebuildQueue();
		dsp->dispatch();

		// XXX XXX DEBUG	
		// XXX AFTER DSP, BEFORE GETPCB
		if(pcb) {
			cout << "Finished/next: ";
			cout << pcb->toString() << endl;
		}

		// XXX DEBUG
		pcb = cpu->getPcb();
		//pcb->printProg(*ram);
		//pcb->printData(*ram);

		// XXX: What the??
		//print_jobs(pList);
		print_ready_jobs(pList);
		cout << endl;

		cout << "Running: ";
		cout << pcb->toString() << endl;

		// XXX XXX: Before the segfault...
		if(pcb->id == 15) {
			//pcb->printProg(*ram);
			//pcb->printData(*ram);
		}

		while(!cpu->isComplete()) {
			cpu->execute();
		}

		// XXX DEBUG
		cout << "Finished: ";
		cout << pcb->toString() << endl;
		//cpu->printRegs();

		// XXX DEBUG 
		cout << endl;

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

