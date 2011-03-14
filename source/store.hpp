#ifndef BT_OS_STORE
#define BT_OS_STORE

#include <vector>
#include <string>
#include "types.hpp"

using namespace std;

/**
 * Store class
 * A type of memory. Registers, Caches, Memory, and Disk are all 
 * implemented with this, either directly or through subclasses. 
 */
class Store 
{
	public:
		/**
		 * Default CTOR.
		 * 1028 words.
		 */
		Store()
			: words(1028, 0),
			allocated(1028, false) {};

		/**
		 * CTOR
		 * Specify the size (in number of words).
		 */
		Store(int size)
			: words(size, 0),
			allocated(size, false) {};

		/**
		 * Get the size of memory.
		 */
		unsigned int size() const { return words.size(); };

		/**
		 * Get the contents of the memory store.
		 * Absolute addressing.
		 */
		word get(unsigned int offset) const;

		/**
		 * Access a single byte at a time.
		 */
		unsigned int getByte(unsigned int offset) const;

		/**
		 * Set the contents of the memory store.
		 * Absolute addressing.
		 */
		void set(unsigned int offset, word data);

		/**
		 * Set a single byte of data.
		 */
		void setByte(unsigned int offset, int data);

		/**
		 * Array access operator.
		 */
		word& operator[](unsigned int offset);

		/**
		 * Clear a single memory location.
		 * It will no longer be marked as allocated.
		 * TODO: Allocation should only be for non-Register memories, yes?
		 */
		void clear(unsigned int offset) { clear(offset, 1); };

		/**
		 * Clear a contiguous memory region.
		 * It will no longer be marked as allocated.
		 * TODO: Allocation should only be for non-Register memories, yes?
		 */
		void clear(unsigned int offset, unsigned int length);

		/**
		 * Determine the number of allocated memory locations.
		 */
		unsigned int numAllocated() const;

		/**
		 * Empty the entire memory store.
		 * TODO: Disable functionality from working in Memory.
		 */
		void reset();

		/**
		 * Print memory
		 * XXX: For debug.
		 */
		string toString() const;
		void writeDisk(string fname);

	protected:
		/**
		 * Memory space.
		 */
		vector<word> words;

		/**
		 * Marks each address as being allocated.
		 * TODO: Allocation should only be for non-Register memories, yes?
		 */
		vector<bool> allocated;
};

#endif
