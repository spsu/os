#ifndef BT_OS_LOADBALANCER
#define BT_OS_LOADBALANCER

class Cpu;
class ProcessList;

// XXX: Needs redesign to support different scheduling algos.

/**
 * Load Balancer
 * Assigns unclaimed processes from RAM to a CPU.
 * Also moves processes from overloaded CPUs to underloaded
 * ones (TODO). Only utilized in Symmetric Multiprocessing.
 */
class LoadBalancer
{
	public:
		/**
		 * CTOR.
		 * Supply pointers to the CPU it is balancing as well
		 * as the *GLOBAL* ProcessList.
		 * TODO: Will need access to a list of all CPUs if 
		 * proper load balancing is to be done. 
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

		// TODO: Actual load balancing!
		// void push();
		// void pull();

		/**
		 * Set to print debug messages about load balancing.
		 */
		void setDebug(bool d) { printDebug = d; };

	private:
		/**
		 * The assigned CPU.
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
