#ifndef BT_OS_MEMORY
#define BT_OS_MEMORY

#include "store.hpp"
#include <pthread.h>
#include <string>

/**
 * Memory class
 * Supports additional higher level operations that the Store class
 * does not, such as locking and finding contiguous free memory.
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
		 * Arbitrary number of words.
		 */
		Memory(int numWords);

		/**
		 * Acquire Mutex Lock 
		 * Locking is not enforced. Caller is responsible for the
		 * use of proper protocols for protecting critical sections.
		 */
		void acquire();

		/**
		 * Release Mutex Lock
		 * Locking is not enforced. Caller is responsible for the
		 * use of proper protocols for protecting critical sections.
		 */
		void release();

		/**
		 * Find empty contiguous free regions of Memory.
		 * This is necessary for loading large processes into memory.
		 */
		int findLargestContiguousHole(unsigned int reqSize) const;
		int findSmallestContiguousHole(unsigned int reqSize) const;

		/**
		 * Mark a contiguous memory region as deallocated. (This makes
		 * it easy to find free regions of available space.)
		 */
		void deallocate(unsigned int offset, unsigned int length = 1);

		/**
		 * Determine the number of allocated memory locations.
		 */
		unsigned int numAllocated() const;

		/**
		 * Write the memory contents to the computer's filesystem 
		 * for report and debugging.
		 */
		void writeDisk(std::string fname);

	private:
		/**
		 * Mutex for memory access.
		 * Users of this class must responsibly use acquire() and 
		 * release().
		 */
		pthread_mutex_t mux;
};

#endif
