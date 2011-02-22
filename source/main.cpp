#include <iostream>
#include <sstream>
#include "loader.hpp"
#include "memory.hpp"
#include "number.hpp"
#include "instruction.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	Loader* a = 0;
	Memory* mem = 0;
	Instruction* instr = 0;

	a = new Loader("data/datafile2.txt");

	mem = new Memory(2048);
	//cout << mem->size() << endl;


	/*cout << hex_to_dec("0A") << endl;
	cout << hex_to_dec("A") << endl;
	cout << hex_to_dec("C0500") << endl;
	cout << hex_to_dec("C05000") << endl;
	cout << hex_to_dec("C050005") << endl;
	cout << hex_to_dec("C050005C") << endl;*/

	// XXX: Memory test
	/*m->set(2030, 0xfff);
	m->set(2031, 9000);
	m->print();*/

	a->loadDisk(mem);

	for(unsigned int i = 0; i < mem->size(); i++)
	{
		instr = new Instruction(mem->get(i));

		cout << "Data " << i << ": ";
		instr->print();
		cout << ",  ";

		delete instr;	
	}

	//mem->print();

	return 0;
}
