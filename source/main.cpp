#include <iostream>
#include <sstream>
#include "loader.hpp"
#include "memory.hpp"
#include "number.hpp"
#include "instruction.hpp"
#include "pcb.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	Loader* loader = 0;
	Memory* mem = 0;
	PcbList* pcbList = 0;
	Instruction* instr = 0;

	loader = new Loader("data/datafile2.txt");
	mem = new Memory(2048);

	pcbList = loader->loadDisk(mem); // TODO: Poor form

	// XXX: Instruction decode test
	for(unsigned int i = 0; i < mem->size(); i++)
	{
		instr = new Instruction(mem->get(i));
		/*cout << "Data " << i << ": ";
		instr->print();
		cout << ",  ";*/
		delete instr;	
	}

	/*
	for(unsigned int i = 0; i < pcbList->size(); i++)
	{
		cout << "================\n";
		cout << pcbList->at(i)->toString() << endl;
		pcbList->at(i)->printCode(*mem);
		cout << endl;
	}*/

	cout << pcbList->at(1)->toString() << endl;
	pcbList->at(1)->printCode(*mem);
	cout << endl;

	//mem->print();

	return 0;
}

