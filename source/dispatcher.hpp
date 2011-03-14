#ifndef BT_OS_DISPATCHER
#define BT_OS_DISPATCHER

#include "pcb.hpp" // TODO: Get rid of this.

class Cpu;
class Memory;
struct ProcessList;

/**
 * TODO/XXX: Keep in mind that I need an m-dispatcher!
 * Would this be better as a function? 
 */
class Dispatcher
{
	public:
		/**
		 * CTOR. (Owns ProcessList)
		 * TODO: Deprecate
		 */
		Dispatcher(Cpu* c, Memory* r);

		/**
		 * CTOR. (Shares ProcessList)
		 */
		Dispatcher(Cpu* c, Memory* r, ProcessList* p);

		/**
		 * DTOR.
		 */
		~Dispatcher();

		/**
		 * Dispatch Pcb -- Test Method
		 * Sets the process represented by the PCB for execution. 
		 * XXX: This is for debugging only.  
		 */
		// TODO: DEPRECATED, DELETE
		void dispatchPcb(Pcb* pcb, Memory* mem);

		/**
		 * Dispatch the next process in the Ready Queue. 
		 * If the current process has not completed, it gets saved
		 * for later resumption. 
		 */
		void dispatch();

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
		 * Process List (and Ownership)
		 * Maintains PCB list and Queues.
		 */
		ProcessList* processList;
		bool ownsProcList;
};

#endif
