#ifndef BT_OS_MEMORY
#define BT_OS_MEMORY

#include "store.hpp"
#include <pthread.h>

/**
 * Memory class
 *    Same as 'Store', but with mutexes.
 *    TODO: mutexes
 */
class Memory : public Store
{
	public:
		/**
		 * Default CTOR.
		 * 1028 words.
		 */
		Memory();

		/**
		 * CTOR
		 * Any number of words.
		 */
		Memory(int numWords);

		/**
		 * Acquire mutex lock.
		 */
		void acquire();

		/**
		 * Release mutex lock.
		 */
		void release();

		/**
		 * Find empty contiguous free regions.
		 */
		int findLargestContiguousHole(unsigned int reqSize) const;
		int findSmallestContiguousHole(unsigned int reqSize) const;

	private:
		/**
		 * Mutex for memory access.
		 * Access methods DO NOT wrap their access!!
		 * Callers must responsibly use acquire() and release().
		 */
		pthread_mutex_t mux;
};

#endif
