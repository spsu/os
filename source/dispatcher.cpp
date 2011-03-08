#include "dispatcher.hpp"
#include "cpu.hpp"
#include "pcb.hpp"

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
		oldProc->registers = cpu->registers;
		oldProc->pc = cpu->pc;
		rq->push(oldProc);
	}

	// Clear CPU
	cpu->registers.reset();
	cpu->cache.reset();
	cpu->pc = 0;
	cpu->process = 0;

	// Dispatch new proc
	newProc = rq->front();
	rq->pop();

	cpu->registers = newProc->registers;
	cpu->pc = newProc->pc;
	cpu->process = newProc;
}

