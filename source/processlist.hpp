#ifndef BT_OS_ACCOUNTING
#define BT_OS_ACCOUNTING

#include <queue>
#include <vector>
#include <pthread.h>

using namespace std;

class Pcb;

/**
 * Maintains a list of processes, Ready Queue, etc.
 * TODO: Better name.
 */
struct ProcessList
{
	public:
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
		 * CTOR.
		 */
		ProcessList();

		/**
		 * Gets the number of jobs that must run or be 
		 * handled in some way. 
		 * Only STATE_TERM_UNLOADED is not counted. 
		 */
		unsigned int numRemainingJobs() const;

		/**
		 * Acquire Mutex Lock 
		 * Locking is not enforced. Caller is responsible for the
		 * use of proper protocols for protecting critical sections.
		 */
		void acquire();

		/**
		 * Release Mutex Lock
		 * Locking is not enforced. Caller is responsible for the
		 * use of proper protocols for protecting critical sections.
		 */
		void release();

		/**
		 * Debugging Methods
		 */
		void printJobs() const;
		void printStates() const;
		void printUnready() const;
		void printReady() const;
		void printDone() const;
		void printDoneValues() const;

	private:
		/**
		 * ProcessList Mutex. 
		 */
		pthread_mutex_t mux;

	
};

#endif
