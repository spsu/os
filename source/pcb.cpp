#include <iostream>
#include <sstream>
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"

using namespace std;

Pcb::Pcb() :
	priority(0),
	jobStart(0),
	jobLength(0),
	dataStart(0),
	dataLength(0),
	dataInLength(0),
	dataOutLength(0),
	dataTempLength(0),
	pc(0),
	regs(16),
	finished(false)
{
	// Nothing
}

string Pcb::toString() const
{
	stringstream s;

	s << "PCB <";
	s << "pri: " << priority << ", ";
	s << "len: " << jobLength << ", " << dataLength;
	//s << " [" << dataInLength << "/" << dataOutLength << "/" << dataTempLength << "]";
	s << ", ";
	s << "start: " << jobStart << ", " << dataStart;
	s << ">";

	return s.str();
}

void Pcb::printProg(const Memory& mem) const
{
	unsigned int start = jobStart;
	unsigned int end = start + jobLength;

	for(unsigned int i = start; i < end; i++)
	{
		Instruction instr(mem.get(i));
		cout << instr.toString();
		cout << endl;
	}
}

void Pcb::printData(const Memory & mem) const
{
	unsigned int end = dataStart + dataLength;
	unsigned int inEnd = dataStart + dataInLength;
	unsigned int outEnd = inEnd + dataOutLength;

	cout << "In >>> ";

	for(unsigned int i = dataStart; i < end; i++) {
		if(i == inEnd) {
			cout << "Out >>> ";
		}
		else if(i == outEnd) {
			cout << "Temp >>> ";
		}
		cout << mem.get(i) << ", \t";
	}
	cout << endl;
}

