#include "stscheduler.hpp"
#include "pcb.hpp"
#include "cpu.hpp"
#include "processlist.hpp"
#include <vector>
#include <iostream>

using namespace std;

void ShortTermScheduler::rebuildQueue()
{
	ProcessList* pList = 0;
	vector<Pcb*> unscheduled;
	Pcb* pcb = 0;

	// TODO TODO TODO TODO ACQUIRE PCB LOCK

	pList = cpu->getProcessList();

	// Get all unscheduled processes. 
	for(unsigned int i = 0; i < pList->all.size(); i++) {
		pcb = pList->all[i];
		if(pcb->state == STATE_NEW_UNSCHEDULED) {
			unscheduled.push_back(pcb);
		}
	}

	if(unscheduled.size() == 0) {
		// Nothing new to schedule... done.
		return;
	}

	// XXX: This isn't really happening yet...
	cout << "[STS] Rebuilding Ready Queue: ";
	cout << unscheduled.size() << " new processes.\n";

	// TODO TODO TODO
	// ONLY DOES FCFS FOR NOW
	for(unsigned int i = 0; i < unscheduled.size(); i++) {
		pcb = unscheduled[i];
		pList->ready.push(pcb);
		pcb->state = STATE_READY;
	}
}

