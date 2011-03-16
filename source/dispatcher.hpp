#ifndef BT_OS_DISPATCHER
#define BT_OS_DISPATCHER

#include "pcb.hpp" // TODO: Get rid of this.

class Cpu;
class Memory;

/**
 * TODO/XXX: Keep in mind that I need an m-dispatcher!
 * Would this be better as a function? 
 */
class Dispatcher
{
	public:
		/**
		 * CTOR.
		 */
		Dispatcher(Cpu* c, Memory* r);

		/**
		 * Dispatch the next process in the Ready Queue. 
		 * If the current process has not completed, it gets saved
		 * for later resumption. 
		 */
		void dispatch();

		/**
		 * Set to print debug messages.
		 */
		void setDebug(bool d) { printDebug = d; };

	private:
		/**
		 * Loads a process to the CPU.
		 * DOES NOT unload the CPU or save any state! 
		 * Make sure to call unloadCpu() first.
		 */
		void loadCpu(Pcb* pcb);

		/**
		 * Offloads process from the CPU.
		 * The process state is recorded in its PCB. 
		 * TODO: Ready Queue
		 */
		void unloadCpu();

		/**
		 * Access to the hardware. 
		 * These are shared pointers.
		 */
		Cpu* cpu;
		Memory* ram;

		/**
		 * Print debugging messages?
		 */
		bool printDebug;
};

#endif
