#ifndef BT_OS_PCB
#define BT_OS_PCB

#include <string>
#include <queue>
#include "types.hpp"
#include "store.hpp"

/**
 * TODO: Documentation.
 */

class Memory;
class Pcb;

typedef std::queue<Pcb*> PcbQueue;

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
		 * Process debugging
		 */
		void printProg(const Memory& mem) const;

		/**
		 * Whether the job has finished.
		 * Set to true when HLT instruction run.
		 */
		bool isFinished() { return finished; };

		// XXX: Data members are *public*
		
		/**
		 * Job priority
		 */
		int priority;

		/**
		 * Memory map
		 */
		int jobStart;
		int jobLength;
		int dataStart;
		int dataLength;
		int dataInLength;
		int dataOutLength;
		int dataTempLength;

		/**
		 * CPU save state
		 */
		word pc;
		Store registers;

	private:
		/**
		 * Whether the job has finished.
		 * Set to true when HLT instruction run.
		 */
		bool finished;
};

#endif
