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

	// Find an unassigned process...
	for(unsigned int i = 0; i < globalList->all.size(); i++) {
		pcb = globalList->all[i];	
		if(pcb->cpuId >= 0) {
			pcb = 0;
			continue;
		}
	}

	if(!pcb) {
		// No process found, we're done.
		return;
	}

	// Assign process to our CPU
	pcb->cpuId = cpu->getId();
	local->all.push_back(pcb);

	cout << "[LoadBalancer] Process " << pcb->id;
	cout << " assigned to CPU " << pcb->cpuId << ".\n";
}
