#include "dispatcher.hpp"
#include "cpu.hpp"
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"
#include <iostream>

// TODO
void Dispatcher::dispatch(PcbQueue* rq)
{
	Pcb* oldProc = 0;
	Pcb* newProc = 0;

	if(rq->empty()) {
		return; // No jobs waiting for us
	}

	// Save old state
	oldProc = cpu->process;
	if(!oldProc->isFinished()) {
		oldProc->regs = cpu->regs;
		oldProc->pc = cpu->pc;
		oldProc->numReadRam = cpu->numReadRam;
		oldProc->numWriteRam = cpu->numWriteRam;
		rq->push(oldProc);
	}

	// Clear CPU
	cpu->regs.reset();
	cpu->cache.reset();
	cpu->pc = 0;
	cpu->process = 0;
	cpu->numReadRam = 0;
	cpu->numWriteRam = 0;

	// Dispatch new proc
	newProc = rq->front();
	rq->pop();

	cpu->regs = newProc->regs;
	cpu->pc = newProc->pc;
	cpu->process = newProc;
	cpu->numReadRam = newProc->numReadRam;
	cpu->numWriteRam = newProc->numWriteRam;

	// TODO TODO TODO
}

void Dispatcher::dispatchPcb(Pcb* pcb, Memory* mem)
{
	// Clear CPU
	cpu->regs.reset();
	cpu->cache.reset();
	cpu->pc = 0;
	cpu->process = 0;

	cpu->regs = pcb->regs;
	cpu->pc = pcb->pc;
	cpu->process = pcb; // XXX/TODO: CPU should call this 'pcb'
	cpu->numReadRam = pcb->numReadRam;
	cpu->numWriteRam = pcb->numWriteRam;

	// Move process code into CPU cache.
	for(unsigned int i = 0; i < pcb->jobLength; i++) {
		cpu->cache.set(i, mem->get(pcb->ram.jobStart + i));

		//Instruction in = Instruction(cpu->cache.get(i)); // XXX: DEBUG
		//cout << in.toString() << endl; // XXX: DEBUG
	}
}

