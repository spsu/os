#ifndef BT_OS_STSCHEDULER
#define BT_OS_STSCHEDULER

class Cpu;

/**
 * CPU Scheduling Algorithms.
 * TODO: These are not yet implemented.
 */
enum CpuScheduleAlgo
{
	// Nonpreemptive scheduling
	SCHEDULE_CPU_FCFS,		// First Come First Serve
	SCHEDULE_CPU_SJF,		// Shortest Job First
	SCHEDULE_CPU_PRIORITY,	// Priority Scheduling

	// Preemptive scheduling (TODO)
	SCHEDULE_CPU_SJF_P,		// Shortest Job First (Preemptive)
	SCHEDULE_CPU_PRIORITY_P	// Priority Scheduling (Preemptive)
};

/**
 * Short Term Scheduler
 * Schedules the Ready Queue for a CPU. Works in both 
 * uniprocessor and multiprocessor cases. 
 *
 * In the uniprocessor case, the CPU's ProcessList is the
 * global ProcessList. The 'ready' queue will be constructed
 * such that it includes all jobs in RAM according to the given
 * scheduling rule. 
 *
 * In the multiprocessor case, the CPU's ProcessList is a
 * local one. It only contains processes that the LoadBalancer 
 * has assigned to the CPU. (This is a Symmetric LoadBalancer:
 * each CPU is self-scheduling.)
 */
class ShortTermScheduler
{
	public:
		/**
		 * CTOR. 
		 * Supply a pointer to the CPU to be scheduled.
		 * TODO: Only does FCFS for now. Implement other algos.
		 */
		ShortTermScheduler(Cpu* c) : 
			cpu(c),
			printDebug(false) {};

		/**
		 * Rebuild the Ready Queue.
		 * This occurs according to the scheduling policy. 
		 */
		void rebuildQueue();

		/**
		 * Set to print debug messages.
		 */
		void setDebug(bool d) { printDebug = d; };

	private:
		/**
		 * The assigned CPU to be scheduled. 
		 */
		Cpu* cpu;

		// TODO: CpuScheduleAlgo algorithm;
		
		/**
		 * Print debugging messages?
		 */
		bool printDebug;
};

#endif
