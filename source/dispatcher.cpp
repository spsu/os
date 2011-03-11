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
		rq->push(oldProc);
	}

	// Clear CPU
	cpu->regs.reset();
	cpu->cache.reset();
	cpu->pc = 0;
	cpu->process = 0;

	// Dispatch new proc
	newProc = rq->front();
	rq->pop();

	cpu->regs = newProc->regs;
	cpu->pc = newProc->pc;
	cpu->process = newProc;

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

	for(unsigned int i = 0; i < pcb->jobLength; i++) {
		cpu->cache.set(i, mem->get(pcb->jobStart + i));

		//Instruction in = Instruction(cpu->cache.get(i)); // XXX: DEBUG
		//cout << in.toString() << endl; // XXX: DEBUG
	}
}

