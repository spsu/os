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
	s << "ram: " << ram.jobStart << ", " << ram.dataStart;
	s << "disk: " << disk.jobStart << ", " << disk.dataStart;
	s << ">";

	return s.str();
}

void Pcb::printProg(const Memory& mem) const
{
	unsigned int start = disk.jobStart;
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
	unsigned int end = disk.dataStart + dataLength;
	unsigned int inEnd = disk.dataStart + dataInLength;
	unsigned int outEnd = inEnd + dataOutLength;

	cout << "In >>> ";

	for(unsigned int i = disk.dataStart; i < end; i++) {
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

