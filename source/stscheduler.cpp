#include "stscheduler.hpp"
#include "pcb.hpp"
#include "cpu.hpp"
#include "accounting.hpp"
#include <vector>

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

	// TODO TODO TODO
	// ONLY DOES FCFS FOR NOW
	for(unsigned int i = 0; i < unscheduled.size(); i++) {
		pcb = unscheduled[i];
		pList->ready.push(pcb);
		pcb->state = STATE_READY;
	}
}

