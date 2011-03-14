#include <iostream>
#include <sstream>
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"

using namespace std;

// Static init
pthread_mutex_t Pcb::mux = PTHREAD_MUTEX_INITIALIZER;

Pcb::Pcb() :
	priority(0),
	state(STATE_NONE),
	jobLength(0),
	dataLength(0),
	dataInLength(0),
	dataOutLength(0),
	dataTempLength(0),
	pc(0),
	regs(16),
	readCount(0),
	writeCount(0)
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
	s << "ram: " << ramPos.jobStart << ", " << ramPos.dataStart;
	s << "disk: " << diskPos.jobStart << ", " << diskPos.dataStart;
	s << ">";

	return s.str();
}

void Pcb::printProg(const Memory& mem) const
{
	unsigned int start = diskPos.jobStart;
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
	unsigned int end = diskPos.dataStart + dataLength;
	unsigned int inEnd = diskPos.dataStart + dataInLength;
	unsigned int outEnd = inEnd + dataOutLength;

	cout << "In >>> ";

	for(unsigned int i = diskPos.dataStart; i < end; i++) {
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

