#ifndef BT_OS_DISPATCHER
#define BT_OS_DISPATCHER

class Cpu;
class Memory;
class Pcb;

/**
 * Dispatcher
 * Unloads the current process from the CPU (saving the state
 * in the PCB) and dispatches the next available process from 
 * the CPU's ProcessList ready queue.
 * Works in both Uniprocessing and Symmetric Multiprocessing
 * cases. 
 */
class Dispatcher
{
	public:
		/**
		 * CTOR.
		 * Supply pointers to the CPU needing the dispatcher
		 * as well as the RAM memory. 
		 */
		Dispatcher(Cpu* c, Memory* r);

		/**
		 * Dispatch the next process in the CPU's ProcessList
		 * Ready Queue. 
		 * If the current process has not completed (ie. it got
		 * interrupted), it gets saved for later resumption. 
		 * (XXX: Interruption is not yet completely supported in 
		 * other code.)
		 */
		void dispatch();

		/**
		 * Set to print debug messages.
		 */
		void setDebug(bool d) { printDebug = d; };

	private:
		/**
		 * Offloads process from the CPU.
		 * The process state is recorded in its PCB. 
		 */
		void unloadCpu();

		/**
		 * Loads a process to the CPU.
		 * DOES NOT unload the CPU or save any state! (That 
		 * is the job of unloadCpu(), so make sure to call 
		 * it first). 
		 */
		void loadCpu(Pcb* pcb);

		/**
		 * Shared pointers.
		 */
		Cpu* cpu;
		Memory* ram;

		/**
		 * Print debugging messages?
		 */
		bool printDebug;
};

#endif
