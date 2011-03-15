#ifndef BT_OS_PCB
#define BT_OS_PCB

#include <string>
#include <queue>
#include <pthread.h>
#include "types.hpp"
#include "store.hpp"

/**
 * TODO: Documentation.
 */

class Memory;
class Cpu;

/**
 * State of a process.
 */
enum ProcessState
{
	STATE_UNDEFINED,	// Not yet created (ie. CTOR ran, but nothing set up.)
	STATE_NEW_UNLOADED,	// Newly created, but not yet in RAM (ie. on disk)
	STATE_NEW_UNSCHEDULED, // Newly created and loaded, but not yet scheduled.
	STATE_READY,		// Ready for CPU
	STATE_RUN,			// Running on CPU
	STATE_WAIT,			// Waiting for device
	STATE_TERM_ON_CPU,	// Finished, but still on the CPU
	STATE_TERM_ON_RAM,	// Finished, but still lives in RAM
	STATE_TERM_UNLOADED	// Finished and relegated back to the Disk
};

/**
 * Process Control Block
 */
class Pcb 
{
	/**
	 * CPU has access to all of PCB's members.
	 */
	friend class Cpu;

	public:
		/**
		 * Default CTOR.
		 */
		Pcb();

		/**
		 * String representation of PCB 
		 */
		std::string toString() const;

		/**
		 * Whether the job has finished.
		 * Set to true when HLT instruction run.
		 */
		bool isFinished() const;

		/**
		 * The total size required on Disk/RAM for the 
		 * process.
		 */
		unsigned int size() const { return jobLength + dataLength; };

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
		void printProg(const Memory& disk) const;
		void printData(const Memory& disk) const;
		std::string stateStr() const;
		word accumulatorValue() const;

		// XXX: Data members are *public*
		
		/**
		 * Job id, priority
		 */
		unsigned int id;
		unsigned int priority;

		/**
		 * Process State
		 */
		ProcessState state;

		/**
		 * Memory lengths 
		 */
		unsigned int jobLength;
		unsigned int dataLength;
		unsigned int dataInLength;
		unsigned int dataOutLength;
		unsigned int dataTempLength;

		/**
		 * Memory map
		 */
		Position diskPos;
		Position ramPos;

		/**
		 * Assigned CPU
		 */
		int cpuId;
		Cpu* cpu; // TODO: Use this instead.

		/**
		 * CPU save state
		 */
		word pc;
		Store regs;

		/**
		 * Statistics
		 * TODO: Wait time, execution time, etc.
		 */
		int readCount;
		int writeCount;

	private:
		/**
		 * PCB mutex. 
		 */
		pthread_mutex_t mux;

		/**
		 * PCB Counter
		 */
		static unsigned int counter;
};

#endif
