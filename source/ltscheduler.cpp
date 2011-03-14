#include "ltscheduler.hpp"
#include "memory.hpp"
#include "accounting.hpp"
#include "pcb.hpp"
#include <vector>
#include <iostream>

using namespace std;

void LongTermScheduler::schedule()
{
	vector<Pcb*> newPcbs;
	Pcb* pcb = 0;

	// TODO TODO TODO: LOCK PROCESS LIST / PCBS

	// Get all of the disk-localized jobs
	for(unsigned int i = 0; i < processList->all.size(); i++) {
		pcb = processList->all[i];
		if(pcb->state == STATE_NEW_UNLOADED) {
			newPcbs.push_back(pcb);
		}
	}

	if(newPcbs.size() == 0) {
		// Nothing left to schedule!
		return;
	}

	ram->acquire();
	disk->acquire();

	for(unsigned int i = 0; i < newPcbs.size(); i++) 
	{
		int pos = 0;
		int size = 0;

		pcb = newPcbs[i];
		size = pcb->size();

		// Find the smallest hole for the process (or abandon)
		pos = ram->findSmallestContiguousHole(size);
		if(pos < 0) {
			continue;
		}

		// Copy Disk to RAM
		for(unsigned int j = 0; j < (unsigned int)size; j++) {
			word w = disk->get(pcb->diskPos.jobStart + j);
			ram->set(pos + j, w);
		}

		// Note result
		pcb->ramPos.jobStart = pos;
		pcb->ramPos.dataStart = pos + pcb->jobLength;
		pcb->state = STATE_NEW_UNSCHEDULED;
	}

	disk->release();
	ram->release();
}

void LongTermScheduler::moveFinishedToDisk()
{
	vector<Pcb*> oldPcbs;
	Pcb* pcb = 0;

	// TODO TODO TODO: LOCK PROCESS LIST / PCBS

	// Get all of the finished, but still RAM-localized jobs
	for(unsigned int i = 0; i < processList->all.size(); i++) {
		pcb = processList->all[i];
		if(pcb->state == STATE_TERM) {
			oldPcbs.push_back(pcb);
		}
	}

	if(oldPcbs.size() == 0) {
		// Nothing is done. 
		return;
	}

	ram->acquire();
	disk->acquire();

	for(unsigned int i = 0; i < oldPcbs.size(); i++) 
	{
		pcb = oldPcbs[i];

		// Copy Process Memory from RAM to Disk
		for(unsigned int j = 0; j < pcb->dataLength; j++) {
			word w = ram->get(pcb->ramPos.dataStart + j);
			ram->set(pcb->diskPos.dataStart + j, w);

		}

		// Mark deallocated.
		ram->clear(pcb->ramPos.jobStart, pcb->size());

		// Note result
		pcb->ramPos.jobStart = -1;
		pcb->ramPos.dataStart = -1;
		pcb->state = STATE_TERM_UNLOADED;
	}

	disk->release();
	ram->release();
}

