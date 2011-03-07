#ifndef BT_OS_DISPATCHER
#define BT_OS_DISPATCHER

class Cpu;
class Pcb;

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

		void dispatch(Pcb* p);

		//void dispatch(Cpu* c, Pcb* p); // XXX: Possible m-dispatcher

	private:
		Cpu* cpu;
};

#endif
