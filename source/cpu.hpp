#ifndef BT_OS_CPU
#define BT_OS_CPU

#include "store.hpp"
#include "types.hpp"
#include <string>

class Pcb;
class ProcessList;
class Memory;

class Cpu 
{
	// XXX: Dispatcher gets to see CPU internals.
	friend class Dispatcher;

	public:
		/**
		 * Uniprocessor CTOR.
		 * Utilizes "global" ProcessList.
		 */
		Cpu(Memory* r, ProcessList* pList);

		/**
		 * Multiprocessor CTOR.
		 * Has its own ProcessList.
		 */
		Cpu(Memory* r);

		/**
		 * DTOR.
		 */
		~Cpu();

		/**
		 * Execute one instruction. 
		 * TODO
		 */
		void execute();

		/**
		 * Returns true if the execution of the current 
		 * process is complete. (ie. HLT reached.)
		 */
		bool isComplete() const;

		/**
		 * Gets the ProcessList for the CPU.
		 */
		ProcessList* getProcessList() { return processList; };

		/**
		 * Gets the PCB assigned to the CPU.
		 * NOTE: State will not be in sync with the CPU!
		 */
		Pcb* getPcb() { return process; };

		/**
		 * String representation of CPU.
		 */
		std::string toString() const;

		/**
		 * Debug methods
		 */
		void printRegs() const;
		word getReg(int reg) const;

	private:
		/**
		 * Effective Addressing (A PCB must be in use)
		 *
		 * Takes a logical address and returns the corresponding
		 * physical address for the currently executing process.
		 *
		 *     * logical -- the logical address
		 *     * convert -- translate byte-indexing into word indexing
		 *
		 *   TODO: If this services more than the CPU, it should be
		 *   moved. 
		 *   TODO: Base reg / index reg, direct/indirect addr ??
		 */
		unsigned int effectiveAddress(unsigned int logical, 
				bool convert = true) const;

		/**
		 * Clear CPU state.
		 * Should only be called by the dispatcher. 
		 */
		void clear();


		/**
		 * Effective Address 
		 * Program counter.
		 *   TODO: Documentation.
		 */
		int pc;

		/**
		 * Registers (16 total).
		 * 	 All registers are general purpose, except:
		 * 	  - 1st is accumulator
		 * 	  - 2nd is zero register
		 */
		Store regs;

		/**
		 * Cache
		 *   Stores the program text section locally.
		 *   Length of 28 will accomodate all processes. 
		 */
		Store cache;

		/**
		 * PCB of the current process running on the CPU.
		 */
		Pcb* process;

		/**
		 * A list of processes assigned to the CPU.
		 * Also, the ownership of the ProcessList. 
		 */
		ProcessList* processList;
		bool ownsProcessList;

		/**
		 * RAM
		 * TODO: Need DMA instead
		 */
		Memory* ram;

		/**
		 * CPU counter.
		 */
		int id;
		static int counter;

		/**
		 * Statistics.
		 */
		int readCount;
		int writeCount;
};

#endif
