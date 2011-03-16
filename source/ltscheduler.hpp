#ifndef BT_OS_LTSCHEDULER
#define BT_OS_LTSCHEDULER

class Memory;
class ProcessList;

// TODO: RAM scheduling algorithms are not yet implemented.
// First Come First Serve is used as default. 
enum RamScheduleAlgo
{
	SCHEDULE_RAM_FCFS,			// Schedule RAM with FCFS 
	SCHEDULE_RAM_PRIORITY,		// Schedule RAM with Priority
	SCHEDULE_RAM_CPU_BOUND,		// Maximize CPU bound processes in RAM
	SCHEDULE_RAM_IO_BOUND,		// Maximize I/O bound processes in RAM
	SCHEDULE_RAM_PROCESS_MIX,	// Maintain a process mix
	SCHEDULE_RAM_MAINTAIN_FULL	// Keep RAM as full as possible
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
		 * Needs shared pointers to Disk, Ram, and
		 * the *GLOBAL* ProcessList. 
		 * TODO: Specify algorithm to use
		 */
		LongTermScheduler(Memory* d, Memory* r, ProcessList* p) :
			disk(d),
			ram(r),
			processList(p) {};

		/**
		 * Schedule RAM
		 * Moves processes from Disk to RAM based on
		 * the scheduling algorithm (FCFS).
		 */
		void schedule();	

	private:
		/**
		 * Move new jobs into RAM when there is 
		 * contiguous space available. 
		 */
		void moveNewToRam();

		/**
		 * Move finished jobs back to Disk, preserving 
		 * their data buffers/state.
		 */
		void moveFinishedToDisk();

		/**
		 * Shared Pointers
		 */
		Memory* disk;
		Memory* ram;
		ProcessList* processList;
};

#endif
