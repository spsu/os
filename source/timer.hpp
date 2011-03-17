#ifndef BT_OS_TIMER
#define BT_OS_TIMER

#include <time.h>
#include <sys/time.h>

/**
 * Timer
 * Record, calculate, and access the time of an event. Time is measured 
 * both in terms of CPU clock ticks as well as wall clock time. 
 */
struct Timer
{
	public:

		/**
		 * CTOR.
		 */
		Timer(): 
			cpuTimeStart(0), 
			cpuTimeTotal(0.0),
			wallTimeTotal(0.0),
			running(false) {};

		/**
		 * Start timer.
		 */
		void start();

		/**
		 * End timer.
		 * If a total already existed, this is added to it.
		 */
		void end();

		/**
		 * Reset the timer.
		 */
		void reset();

		/**
		 * Returns the run time with respect to the CPU's clock ticks.
		 * (ie. If the event is suspended, the timer does not observe 
		 * the passage of time.) Time is in seconds. 
		 */
		double getCpuTime() const;

		/**
		 * Returns the run time with respect to an external observer,
		 * AKA "wall clock" time. Time is in seconds. 
		 */
		double getWallTime() const;

	private:
		/**
		 * Physical CPU and Wall time start points. These values are
		 * subtracted from whenever the "current time" is measured.
		 * Values for each are in different formats. 
		 */
		clock_t cpuTimeStart;
		timeval wallTimeStart;

		/**
		 * Totals for CPU and Wall time. Values are in seconds. 
		 */
		double cpuTimeTotal;
		double wallTimeTotal;

		/**
		 * Whether timer is running.
		 */
		bool running;
};

#endif
