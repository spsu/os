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
		Dispatcher(Cpu* c)
			: cpu(c) {};

		/**
		 * Dispatch the next process in the Ready Queue. 
		 * If the current process has not completed, shelve it for later. 
		 * (TODO: Wait queue, IO queue, etc.)
		 */
		void dispatch(PcbQueue* rq);

		/**
		 * Dispatch Pcb -- Test Method
		 * Sets the process represented by the PCB for execution. 
		 * XXX: This is for debugging only.  
		 */
		void dispatchPcb(Pcb* pcb, Memory* mem);

		/**
		 * Offloads process from the CPU. 
		 * TODO: Ready Queue
		 */
		//void shelvePcb();

		//void dispatch(Cpu* c, Pcb* p); // XXX: Possible m-dispatcher

	private:
		Cpu* cpu;
};

#endif
