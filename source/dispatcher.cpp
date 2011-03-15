#include "dispatcher.hpp"
#include "processlist.hpp"
#include "cpu.hpp"
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"
#include <iostream>

Dispatcher::Dispatcher(Cpu* c, Memory* r) :
	cpu(c),
	ram(r)
{
	// Nothing
}

void Dispatcher::dispatch()
{
	ProcessList* pList = 0;
	Pcb* pcb = 0;

	unloadCpu();

	pList = cpu->getProcessList();

	if(pList->ready.size() == 0) {
		// TODO: All -- signal scheduler?
		// TODO: SMP -- signal load balancer?
		return;
	}

	pcb = pList->ready.front();
	pList->ready.pop();

	loadCpu(pcb);
}

void Dispatcher::loadCpu(Pcb* pcb)
{
	cout << "[Dispatcher] Loading: " << pcb->id << endl;

	pcb->acquire();

	cpu->process = pcb;
	cpu->regs = pcb->regs;
	cpu->pc = pcb->pc;
	cpu->readCount = pcb->readCount;
	cpu->writeCount = pcb->writeCount;

	// XXX: This should only be necessary in the uniprocessor case
	if(pcb->cpuId < 0) {
		pcb->cpuId = cpu->id;
	}

	// Move process code into CPU cache.
	ram->acquire();
	for(unsigned int i = 0; i < pcb->jobLength; i++) {
		cpu->cache.set(i, ram->get(pcb->ramPos.jobStart + i));
	}
	ram->release();
	pcb->release();
}

void Dispatcher::unloadCpu()
{
	ProcessList* pList = 0;
	Pcb* pcb = 0;

	if(!cpu->process) {
		// Nothing to unload.
		// Perhaps an interrupt occurred and was already handled. Exit.
		cpu->clear();
		return;
	}

	pcb = cpu->process;
	pcb->acquire();

	// Save old state
	pcb->regs = cpu->regs;
	pcb->pc = cpu->pc;
	pcb->readCount = cpu->readCount;
	pcb->writeCount = cpu->writeCount;

	cout << "[Dispatcher] Unloaded: " << pcb->id << endl;

	// Return interrupted processes to the Ready Queue
	// TODO: Should the CPU even set PCB attrs?
	if(!pcb->isFinished()) {
		pcb->state = STATE_READY;
		pList = cpu->getProcessList();
		pList->ready.push(pcb);
	}
	else {
		pcb->state = STATE_TERM_ON_RAM;
	}

	pcb->release();

	// Clear CPU state. 
	cpu->clear();
}

