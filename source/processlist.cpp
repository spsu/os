#include "processlist.hpp"
#include "pcb.hpp"
#include <iostream>

using namespace std;

unsigned int ProcessList::numRemainingJobs() const
{
	unsigned int cnt = 0;

	for(unsigned int i = 0; i < all.size(); i++) {
		if(all[i]->state != STATE_TERM_UNLOADED) {
			cnt++;	
		}
	}
	return cnt;	
}

void ProcessList::printJobs() const
{
	for(unsigned int i = 0; i < all.size(); i++)
		cout << all[i]->toString() << endl;
}

void ProcessList::printStates() const
{
	for(unsigned int i = 0; i < all.size(); i++) {
		cout << "PCB[";
		cout << all[i]->id << "]: ";
		cout << all[i]->stateStr() << ",  ";
	}
}

void ProcessList::printUnready() const
{
	cout << "Unready: ";
	for(unsigned int i = 0; i < all.size(); i++) {
		switch(all[i]->state) {
			case STATE_UNDEFINED:
			case STATE_NEW_UNLOADED:
			case STATE_NEW_UNSCHEDULED:
				cout << all[i]->id << ", ";
			default:
				continue;
		}
	}
	cout << endl;
}

void ProcessList::printReady() const
{
	cout << "Ready: ";
	for(unsigned int i = 0; i < all.size(); i++) {
		if(all[i]->state == STATE_READY) {
			cout << all[i]->id << ", ";
		}
	}
	cout << endl;
}

void ProcessList::printDone() const
{
	cout << "Done: ";
	for(unsigned int i = 0; i < all.size(); i++) {
		switch(all[i]->state) {
			case STATE_TERM_ON_CPU:
			case STATE_TERM_ON_RAM:
			case STATE_TERM_UNLOADED:
				cout << all[i]->id << ", ";
			default:
				continue;
		}
	}
	cout << endl;
}

void ProcessList::printDoneValues() const
{
	cout << "Done Values: ";
	for(unsigned int i = 0; i < all.size(); i++) {
		switch(all[i]->state) {
			case STATE_TERM_ON_RAM:
			case STATE_TERM_UNLOADED:
				cout << all[i]->id << ": ";
				cout << all[i]->accumulatorValue() << ", ";
			default:
				continue;
		}
	}
	cout << endl;
}

