#ifndef BT_OS_MEMORY
#define BT_OS_MEMORY

#include <vector>
#include "types.hpp"

using namespace std;

/**
 * Memory class
 */
class Memory
{
	public:
		/**
		 * Default CTOR.
		 * 1028 words.
		 */
		Memory()
			: words(1028, 0) {};

		/**
		 * CTOR
		 * Any number of words.
		 */
		Memory(int numWords)
			: words(numWords, 0) {};

		/**
		 * Get the size of memory.
		 */
		int size() { return words.size(); };

		/**
		 * Get the contents of the memory.
		 * Absolute addressing.
		 */
		word get(int offset);

		/**
		 * Set the contents of the memory.
		 * Absolute addressing.
		 */
		void set(int offset, word data);

		/**
		 * Print memory
		 * XXX: For debug.
		 */
		void print();

	private:
		/**
		 * Memory space.
		 */
		vector<word> words;
};

#endif
