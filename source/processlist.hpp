#ifndef BT_OS_ACCOUNTING
#define BT_OS_ACCOUNTING

#include <queue>
#include <vector>

using namespace std;

class Pcb;

/**
 * Maintains a list of processes, Ready Queue, etc.
 * TODO: Better name.
 */
struct ProcessList
{
	/**
	 * All known processes, finished and otherwise.
	 * PCBs are added as processes are loaded from the batch 
	 * file.
	 */
	vector<Pcb*> all;

	/**
	 * Ready Queue
	 * Processes in RAM that are in contention for a CPU.
	 */
	queue<Pcb*> ready;

	/**
	 * Wait Queue
	 * Processes in RAM that are waiting for an event.
	 */
	queue<Pcb*> wait;

	/**
	 * Gets the number of jobs that must run or be 
	 * handled in some way. 
	 * Only STATE_TERM_UNLOADED is not counted. 
	 */
	unsigned int numRemainingJobs() const;

	/**
	 * Debugging Methods
	 */
	void printJobs() const;
	void printStates() const;
	void printUnready() const;
	void printReady() const;
	void printDone() const;
	void printDoneValues() const;
};

#endif
