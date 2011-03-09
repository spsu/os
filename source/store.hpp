#ifndef BT_OS_STORE
#define BT_OS_STORE

#include <vector>
#include <string>
#include "types.hpp"

using namespace std;

/**
 * Store class
 * A type of memory. Registers, Caches, Memory, and Disk are all 
 * implemented with this, either directly or throug subclasses. 
 */
class Store 
{
	public:
		/**
		 * Default CTOR.
		 * 1028 words.
		 */
		Store()
			: words(1028, 0) {};

		/**
		 * CTOR
		 * Any number of words.
		 */
		Store(int numWords)
			: words(numWords, 0) {};

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
		 * Empty the entire memory store.
		 * TODO: Disable functionality from working in Memory.
		 */
		void reset();

		/**
		 * Print memory
		 * XXX: For debug.
		 */
		string toString() const;

	protected:
		/**
		 * Memory space.
		 */
		vector<word> words;
};

#endif
