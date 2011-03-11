#ifndef BT_OS_CPU
#define BT_OS_CPU

#include "store.hpp"

class Pcb;
class Memory;

class Cpu 
{
	// XXX: Dispatcher gets to see CPU internals.
	friend class Dispatcher;

	public:
		/**
		 * CTOR.
		 * Needs access to RAM. 
		 */
		Cpu(Memory* r);

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
		 * Debug methods
		 */
		void printRegs() const;

	private:
		/**
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
		 * RAM
		 *   TODO: Need DMA instead
		 */
		Memory* ram;
};

#endif
