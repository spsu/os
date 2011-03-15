#ifndef BT_OS_LTSCHEDULER
#define BT_OS_LTSCHEDULER

class Memory;
class ProcessList;

enum DiskScheduleAlgo
{
	SCHEDULE_RAM_CPU_BOUND,		// Maximize CPU bound processes in RAM
	SCHEDULE_RAM_IO_BOUND,		// Maximize I/O bound processes in RAM
	SCHEDULE_RAM_PROCESS_MIX,	// Maintain a process mix
	SCHEDULE_RAM_MAINTAIN_FULL	// Keep RAM as full as possible
};

class LongTermScheduler
{
	public:
		/**
		 * CTOR
		 * Loads Disk to RAM (and unloads RAM to Disk).
		 * Needs accesses to the *global* ProcessList.
		 * TODO: Specify algorithm to use
		 */
		LongTermScheduler(Memory* d, Memory* r, ProcessList* p) :
			disk(d),
			ram(r),
			processList(p) {};

		/**
		 * Schedule RAM
		 * Moves processes from Disk to Ram.
		 * TODO TODO TODO: LOCK PROCESS LIST / PCBS
		 */
		void schedule();	

	private:
		/**
		 * Move new jobs into RAM
		 * TODO TODO TODO: LOCK PROCESS LIST / PCBS
		 */
		void moveNewToRam();

		/**
		 * Move finished jobs back to Disk.
		 * Saves the memory state. 
		 * TODO TODO TODO: LOCK PROCESS LIST / PCBS
		 */
		void moveFinishedToDisk();

		/**
		 * Disk and RAM shared ptrs.
		 */
		Memory* disk;
		Memory* ram;
		ProcessList* processList;
};

#endif
