#include <iostream>
#include <sstream>
#include "loader.hpp"
#include "memory.hpp"
#include "number.hpp"
#include "instruction.hpp"
#include "pcb.hpp"
#include "cpu.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	Loader* loader = 0;
	Memory* mem = 0;
	PcbList* pcbList = 0;

	loader = new Loader("data/datafile2.txt");
	mem = new Memory(2048);

	pcbList = loader->loadDisk(mem); // TODO: Poor form

	cout << mem->toString();

	return 0;

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

	Cpu* cpu = new Cpu();
	delete cpu;

	return 0;
}

