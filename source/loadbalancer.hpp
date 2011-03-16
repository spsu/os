#ifndef BT_OS_LOADBALANCER
#define BT_OS_LOADBALANCER

class Cpu;
class ProcessList;

/**
 * Load Balancing
 * Only relevant in multiprocessing cases.
 * Built for symmetric multiprocessing.
 */
class LoadBalancer
{
	public:
		/**
		 * CTOR.
		 */
		LoadBalancer(Cpu* c, ProcessList* global) :
			cpu(c),
			globalList(global),
			printDebug(false) {};

		/**
		 * Import a single new process to the CPU.
		 * TODO: For now, only one process is imported. When 
		 * interruption is implemented, importing a variable 
		 * number may be interesting. Then push()/pull() can 
		 * work to dynamically balance the load. 
		 */
		void importNewProcess();

		// TODO:
		// void push();
		// void pull();

		/**
		 * Set to print debug messages.
		 */
		void setDebug(bool d) { printDebug = d; };

	private:
		/**
		 * The assigned CPU
		 */
		Cpu* cpu;

		/**
		 * The GLOBAL ProcessList.
		 * This is not the CPU's local one.
		 */
		ProcessList* globalList;

		/**
		 * Print debugging messages?
		 */
		bool printDebug;
};

#endif
