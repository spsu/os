#ifndef BT_OS_LTSCHEDULER
#define BT_OS_LTSCHEDULER

#include <vector>

class Memory;
class ProcessList;
class Pcb;

// RAM scheduling algorithms.
// First Come First Serve is used as default. 
enum RamScheduleAlgorithm
{
	// Schedule RAM with First Come First Serve. Jobs are brought into 
	// RAM from Disk in the same order they were loaded from the batch 
	// file.
	SCHEDULE_RAM_FCFS,

	// Schedule RAM with Priority. Bring jobs in from the Disk in the 
	// order of their numeric priority. High number = high priority. 
	SCHEDULE_RAM_PRIORITY

	// TODO: Might be interesting to investigate: 
	//SCHEDULE_RAM_CPU_BOUND,	// Maximize CPU bound processes in RAM
	//SCHEDULE_RAM_IO_BOUND,	// Maximize I/O bound processes in RAM
	//SCHEDULE_RAM_PROCESS_MIX,	// Maintain a process mix
	//SCHEDULE_RAM_MAINTAIN_FULL // Keep RAM as full as possible
};

/**
 * Long Term Scheduler.
 * Schedules what jobs are to be loaded into RAM from the Disk.
 * This runs in both Uniprocessor and Symmetric Multiprocessing
 * cases. 
 */
class LongTermScheduler
{
	public:
		/**
		 * CTOR
		 * Needs shared pointers to Disk, Ram, and the *GLOBAL* 
		 * ProcessList. You may also supply the scheduling algorithm
		 * that is to be used. 
		 */
		LongTermScheduler(Memory* d, Memory* r, ProcessList* p, 
				RamScheduleAlgorithm a = SCHEDULE_RAM_FCFS) :
			disk(d),
			ram(r),
			processList(p),
			policy(a),
			printDebug(false) {};

		/**
		 * Schedule RAM
		 * Moves processes from Disk to RAM based on the scheduling 
		 * algorithm.
		 */
		void schedule();	

		/**
		 * Set to print debug messages.
		 */
		void setDebug(bool d) { printDebug = d; };

	private:
		/**
		 * Move finished jobs back to Disk, preserving their data 
		 * buffers/state.
		 */
		void moveFinishedToDisk();

		/**
		 * Find new jobs and load them into RAM as long as there is 
		 * sufficient contiguous space available. The processes are
		 * loaded according to the scheduling policy. 
		 */
		void moveNewToRam();

		/**
		 * These methods do the work of moveNewToRam().
		 * Each implements a different algorithm. 
		 */
		void moveToRamFcfs(std::vector<Pcb*> pcbs);
		void moveToRamPriority(std::vector<Pcb*> pcbs);
		/**
		 * Shared Pointers
		 */
		Memory* disk;
		Memory* ram;
		ProcessList* processList;

		/**
		 * Scheduling policy
		 */
		RamScheduleAlgorithm policy;

		/**
		 * Print debugging messages?
		 */
		bool printDebug;
};

#endif
