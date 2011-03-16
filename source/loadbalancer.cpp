#include "loadbalancer.hpp"
#include "processlist.hpp"
#include "cpu.hpp"
#include "pcb.hpp"
#include <iostream>

void LoadBalancer::importNewProcess()
{
	ProcessList* local = 0;
	Pcb* pcb = 0;

	local = cpu->getProcessList();

	// Make sure import occurs without race cond.
	globalList->acquire();

	// Find an unassigned process in the correct state...
	for(unsigned int i = 0; i < globalList->all.size(); i++) {
		pcb = globalList->all[i];
		if(pcb->cpuId < 0 && pcb->state == STATE_NEW_UNSCHEDULED) {
			break;
		}
		pcb = 0;
	}

	if(!pcb) {
		// No process found, we're done.
		globalList->release();
		return;
	}

	// Assign process to our CPU
	pcb->cpuId = cpu->getId();
	local->all.push_back(pcb);

	if(printDebug) {
		cout << "[LoadBalancer] Process " << pcb->id;
		cout << " assigned to CPU " << pcb->cpuId << ".\n";
	}

	globalList->release();
}
