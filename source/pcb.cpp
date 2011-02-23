#include <iostream>
#include <sstream>
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"

using namespace std;

string Pcb::toString() const
{
	stringstream s;

	s << "PCB <";
	s << "pri: " << priority << ", ";
	s << "prog@: " << diskInstructionsStart << ", "; // TODO: dec_to_hex
	s << "len: " << diskInstructionsLimit; // TODO: dec_to_hex
	s << ">";

	return s.str();
}

void Pcb::printProg(const Memory& mem) const
{
	unsigned int start = diskInstructionsStart;
	unsigned int end = start + diskInstructionsLimit;

	for(unsigned int i = start; i < end; i++)
	{
		Instruction instr(mem.get(i));
		cout << instr.toString();
		cout << endl;
	}
}

/*void Pcb::printData()
{
	// TODO
	cout << "TODO: Pcb::printData()\n";
}*/

