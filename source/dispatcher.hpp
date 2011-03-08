#ifndef BT_OS_DISPATCHER
#define BT_OS_DISPATCHER

#include "pcb.hpp" // TODO: Get rid of this.

class Cpu;

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
		 * Dispatch a process from the Ready Queue. 
		 */
		void dispatch(PcbQueue* rq);

		//void dispatch(Cpu* c, Pcb* p); // XXX: Possible m-dispatcher

	private:
		Cpu* cpu;
};

#endif
