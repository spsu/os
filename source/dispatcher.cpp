#include "dispatcher.hpp"
#include "accounting.hpp"
#include "cpu.hpp"
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"
#include <iostream>

Dispatcher::Dispatcher(Cpu* c, Memory* r) :
	cpu(c),
	ram(r),
	processList(0),
	ownsProcList(true)
{
	processList = new ProcessList();
}

Dispatcher::Dispatcher(Cpu* c, Memory* r, ProcessList* p) :
	cpu(c),
	ram(r),
	processList(p),
	ownsProcList(false)
{
	// Nothing
}

Dispatcher::~Dispatcher()
{
	if(ownsProcList) {
		delete processList;
	}
}

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
		oldProc->readCount = cpu->readCount;
		oldProc->writeCount = cpu->writeCount;
		rq->push(oldProc);
	}

	// Clear CPU
	cpu->clear();
	
	// Dispatch new proc
	newProc = rq->front();
	rq->pop();

	cpu->regs = newProc->regs;
	cpu->pc = newProc->pc;
	cpu->process = newProc;
	cpu->readCount = newProc->readCount;
	cpu->writeCount = newProc->writeCount;

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
	cpu->readCount = pcb->readCount;
	cpu->writeCount = pcb->writeCount;

	// Move process code into CPU cache.
	for(unsigned int i = 0; i < pcb->jobLength; i++) {
		cpu->cache.set(i, mem->get(pcb->ramPos.jobStart + i));

		//Instruction in = Instruction(cpu->cache.get(i)); // XXX: DEBUG
		//cout << in.toString() << endl; // XXX: DEBUG
	}
}

void Dispatcher::dispatch()
{

}

void Dispatcher::loadCpu(Pcb* pcb)
{
	cpu->process = pcb;
	cpu->regs = pcb->regs;
	cpu->pc = pcb->pc;
	cpu->readCount = pcb->readCount;
	cpu->writeCount = pcb->writeCount;

	// Move process code into CPU cache.
	ram->acquire();
	for(unsigned int i = 0; i < pcb->jobLength; i++) {
		cpu->cache.set(i, ram->get(pcb->ramPos.jobStart + i));
	}
	ram->release();
}

void Dispatcher::unloadCpu()
{
	Pcb* pcb = 0;

	if(!cpu->process) {
		// Nothing to unload.
		// Perhaps an interrupt occurred and was already handled. Exit.
		cpu->clear();
		return;
	}

	// Save old state
	pcb = cpu->process;
	pcb->regs = cpu->regs;
	pcb->pc = cpu->pc;
	pcb->readCount = cpu->readCount;
	pcb->writeCount = cpu->writeCount;

	// Return interrupted processes to the Ready Queue
	// TODO: Should the CPU even set PCB attrs?
	if(!pcb->isFinished()) {
		pcb->state = STATE_READY;
		processList->ready.push(pcb);
	}
	else {
		pcb->state = STATE_TERM;
	}

	// Clear CPU state. 
	cpu->clear();
}

