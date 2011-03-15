#include "ltscheduler.hpp"
#include "memory.hpp"
#include "processlist.hpp"
#include "pcb.hpp"
#include <vector>
#include <iostream>

using namespace std;

void LongTermScheduler::schedule()
{
	moveFinishedToDisk();
	moveNewToRam();
}

void LongTermScheduler::moveNewToRam()
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

		cout << "[LTS] Loading process " << pcb->id << " (size: ";
		cout << pcb->size() << ") into RAM at position ";
		cout << pos << ".\n";
	}

	disk->release();
	ram->release();
}

void LongTermScheduler::moveFinishedToDisk()
{
	vector<Pcb*> finished;
	Pcb* pcb = 0;

	// TODO TODO TODO: LOCK PROCESS LIST / PCBS

	// Get all of the finished, but still RAM-localized jobs
	for(unsigned int i = 0; i < processList->all.size(); i++) {
		pcb = processList->all[i];
		if(pcb->state == STATE_TERM_ON_RAM) {
			finished.push_back(pcb);
		}
	}

	if(finished.size() == 0) {
		// Nothing is done. 
		return;
	}

	ram->acquire();
	disk->acquire();

	for(unsigned int i = 0; i < finished.size(); i++) 
	{
		pcb = finished[i];

		// Copy Process Data Memory from RAM to Disk
		for(unsigned int j = 0; j < pcb->dataLength; j++) {
			word w = ram->get(pcb->ramPos.dataStart + j);
			disk->set(pcb->diskPos.dataStart + j, w);
		}

		// Mark RAM deallocated.
		ram->clear(pcb->ramPos.jobStart, pcb->size());

		// Note result in PCB
		pcb->ramPos.jobStart = -1;
		pcb->ramPos.dataStart = -1;
		pcb->state = STATE_TERM_UNLOADED;

		cout << "[LTS] Unloaded process " << pcb->id << " ";
		cout << "(size: " << pcb->size() << ") to Disk.\n";
	}

	disk->release();
	ram->release();
}

