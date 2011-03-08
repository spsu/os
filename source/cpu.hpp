#ifndef BT_OS_CPU
#define BT_OS_CPU

#include "store.hpp"

class Pcb;

class Cpu 
{
	// XXX: Dispatcher gets to see CPU internals.
	friend class Dispatcher;

	public:
		/**
		 * CTOR.
		 */
		Cpu();

		/**
		 * Execute loop.
		 * TODO
		 */
		void execute();

	private:
		/**
		 * Registers (16 total).
		 * 	 All registers are general purpose, except:
		 * 	  - 1st is accumulator
		 * 	  - 2nd is zero register
		 */
		Store registers;

		/**
		 * Cache
		 *   Stores the program text section locally.
		 *   Length of 28 will accomodate all processes. 
		 */
		Store cache;

		/**
		 * Program counter.
		 *   TODO: Documentation.
		 */
		word pc;

		/**
		 * PCB of the current process running on the CPU.
		 */
		Pcb* process;
};

#endif
