#include <iostream>
#include <sstream>
#include "loader.hpp"
#include "memory.hpp"
#include "number.hpp"
#include "instruction.hpp"
#include "dispatcher.hpp"
#include "pcb.hpp"
#include "cpu.hpp"

using namespace std;

/**
 * Debug func
 */
void print_pcbs(PcbList& pcbs) {
	for(unsigned int i = 0; i < pcbs.size(); i++)
		cout << pcbs.at(i)->toString() << endl;
}

/**
 * Main func
 */
int main(int argc, char *argv[])
{
	Loader* loader = 0;
	Memory* mem = 0;
	PcbList* pcbList = 0;
	Pcb* pcb = 0;
	Cpu* cpu = 0;
	Dispatcher* disp = 0;

	loader = new Loader("data/datafile2.txt");
	mem = new Memory(2048);

	cpu = new Cpu(mem);
	disp = new Dispatcher(cpu);

	pcbList = loader->loadDisk(mem); // TODO: Poor form	
	//print_pcbs(*pcbList);

	pcb = pcbList->at(2);
	
	cout << "=============================================" << endl;
	pcb->printProg(*mem);
	cout << "=============================================" << endl;

	disp->dispatchPcb(pcb, mem);

	cout << "Data memory before run: ";
	cout << "\n------------------\n";
	pcb->printData(*mem);
	cout << "\n------------------\n";
	cout << endl;

	while(!cpu->isComplete()) {
		cpu->execute();
	}

	cout << "Data memory after run: ";
	cout << "\n------------------\n";
	pcb->printData(*mem);
	cout << "\n------------------\n";
	
	cpu->printRegs();
	cout << endl;

	return 0;	
	
	cout << "Data memory AFTER run: ";
	cout << mem->get(43) << endl;
	cout << dec_to_bin(mem->get(43)) << endl;	// PROGRAM OUTPUT LOCATION


	// XXX: Instruction decode test
	/*for(unsigned int i = 0; i < mem->size(); i++)
	{
		Instruction* instr = new Instruction(mem->get(i));
		//cout << "Data " << i << ": ";
		//instr->print();
		//cout << ",  ";
		delete instr;	
	}*/

	// Print processes
	/*for(unsigned int i = 0; i < pcbList->size(); i++)
	{
		cout << "================\n";
		cout << pcbList->at(i)->toString() << endl;
		pcbList->at(i)->printProg(*mem);
		cout << endl;
	}*/

	//mem->print();


	return 0;
}

