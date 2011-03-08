#ifndef BT_OS_SCHEDULER
#define BT_OS_SCHEDULER

class Scheduler
{
	public:
		/**
		 * CTOR.
		 */
		Scheduler();


		/**
		 * Long-term scheduler.
		 *   Decides which jobs to bring from the disk
		 *   into memory.
		 */
		void scheduleMem();

		/**
		 * Short-term scheduler.
		 *   Decides which job from memory should be 
		 *   scheduled for the CPU next.
		 */
		void scheduleCpu();

};

#endif
