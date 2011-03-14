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
class Pcb;

typedef std::queue<Pcb*> PcbQueue;

/**
 * State of any given process.
 */
enum ProcessState
{
	STATE_NONE,		// Not yet created
	STATE_NEW,		// Newly created
	STATE_READY,	// Ready for CPU
	STATE_RUN,		// Running on CPU
	STATE_WAIT,		// Waiting for device
	STATE_TERM		// Finished
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
		bool isFinished() { return (state == STATE_TERM); };

		/**
		 * Debugging Methods
		 */
		void printProg(const Memory& disk) const;
		void printData(const Memory& disk) const;

		// XXX: Data members are *public*
		
		/**
		 * Job priority
		 */
		unsigned int priority;

		/**
		 * Process State
		 */
		ProcessState state;

		/**
		 * Memory map
		 */
		unsigned int jobLength;
		unsigned int dataLength;
		unsigned int dataInLength;
		unsigned int dataOutLength;
		unsigned int dataTempLength;

		/**
		 * New memory map
		 */
		Position disk;
		Position ram;

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
		 * Global PCB locking. 
		 * When any PCB is being accessed, all are locked.
		 */
		static pthread_mutex_t mux;
};

#endif
