#ifndef BT_OS_STSCHEDULER
#define BT_OS_STSCHEDULER

class Cpu;

/**
 * CPU Scheduling Algorithms.
 * TODO
 */
/*enum CpuScheduleAlgo
{
	// Nonpreemptive scheduling
	SCHEDULE_FCFS,		// First Come First Serve
	SCHEDULE_SJF,		// Shortest Job First
	SCHEDULE_PRIORITY,	// Priority Scheduling

	// Preemptive scheduling (TODO)
	SCHEDULE_SJF_P,		// Shortest Job First (Preemptive)
	SCHEDULE_PRIORITY_P	// Priority Scheduling (Preemptive)
};*/

/**
 * Short Term Scheduler.
 */
class ShortTermScheduler
{
	public:
		/**
		 * CTOR. (First Come First Serve)
		 * TODO: Other sched. algos.
		 */
		ShortTermScheduler(Cpu* c) : cpu(c) {};

		/**
		 * Rebuild the Ready Queue.
		 * TODO TODO TODO: Acquire locks properly (Esp. PCB/pList)
		 */
		void rebuildQueue();

	private:
		/**
		 * Assigned CPU. 
		 */
		Cpu* cpu;

		// TODO: CpuScheduleAlgo algorithm;
};

#endif
