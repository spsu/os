#include <iostream>
#include <sstream>
#include "accounting.hpp"
#include "loader.hpp"
#include "memory.hpp"
#include "number.hpp"
#include "instruction.hpp"
#include "dispatcher.hpp"
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

void run_jobs(Cpu* cpu, Memory* mem, ProcessList* pList)
{
	Dispatcher* dsp = 0;
	Pcb* pcb = 0;

	dsp = new Dispatcher(cpu);

	for(unsigned int i = 0; i < pList->all.size(); i++) {
		pcb = pList->all.at(i);
		dsp->dispatchPcb(pcb, mem);

		while(!cpu->isComplete()) {
			cpu->execute();
		}
		cout << "Process " << i << ": ";
		cout << cpu->getReg(0) << "\t";
		cout << cpu->numReadRam << "\t" << cpu->numWriteRam; 
		cout << endl;
	}
}

/**
 * Main func
 */
int main(int argc, char *argv[])
{
	Loader* loader = 0;
	Memory* mem = 0;
	ProcessList* pList = 0;
	Cpu* cpu = 0;
	Dispatcher* disp = 0;

	loader = new Loader("data/datafile2.txt");
	mem = new Memory(2048);

	cpu = new Cpu(mem);
	disp = new Dispatcher(cpu);

	pList = loader->loadDisk(mem); // TODO: Poor form	
	
	// XXX: DEBUG
	run_jobs(cpu, mem, pList);

	return 0;	
}

