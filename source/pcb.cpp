#include <iostream>
#include <sstream>
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"

using namespace std;

// Static init
unsigned int Pcb::counter = 0;

Pcb::Pcb() :
	id(0),
	priority(0),
	state(STATE_UNDEFINED),
	jobLength(0),
	dataLength(0),
	dataInLength(0),
	dataOutLength(0),
	dataTempLength(0),
	cpuId(-1),
	pc(0),
	regs(16),
	readCount(0),
	writeCount(0)
{
	id = counter;
	counter++;

	pthread_mutex_init(&mux, NULL);
}

string Pcb::toString() const
{
	stringstream s;

	s << "PCB " << id << " <";
	s << "p: " << priority << ", ";
	s << "sz: " << size() << ", "; 
	s << "R:: " << ramPos.jobStart << ", ";
	s << "D: " << diskPos.jobStart << ", ";
	s << "C: " << cpuId << ", ";
	s << stateStr() << ", ";
	s << accumulatorValue() << ", ";
	s << "r: " << runTime.getCpuTime() << "s, ";
	s << runTime.getWallTime() << "s";
	s << "w: " << waitTime.getCpuTime() << "s, ";
	s << waitTime.getWallTime() << "s";
	s << ">";

	return s.str();
}

bool Pcb::isFinished() const
{
	return (state == STATE_TERM_ON_CPU ||
			state == STATE_TERM_ON_RAM ||
			state == STATE_TERM_UNLOADED);
}

void Pcb::acquire()
{
	pthread_mutex_lock(&mux);
}

void Pcb::release()
{
	pthread_mutex_unlock(&mux);
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

string Pcb::stateStr() const
{
	switch(state) {
		case STATE_UNDEFINED:
			return "Not Created";
		case STATE_NEW_UNLOADED:
			return "New/Disk";
		case STATE_NEW_UNSCHEDULED:
			return "New/RAM";
		case STATE_READY:
			return "Ready";
		case STATE_RUN:
			return "Running";
		case STATE_WAIT:
			return "Waiting";
		case STATE_TERM_ON_CPU:
			return "Term/CPU";
		case STATE_TERM_ON_RAM:
			return "Term/RAM";
		case STATE_TERM_UNLOADED:
			return "Term/Disk";
	}
	return "Unknown";
}

word Pcb::accumulatorValue() const
{
	// DOES NOT reflect value on CPU
	return regs.get(0);	
}

