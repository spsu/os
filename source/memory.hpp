#ifndef BT_OS_MEMORY
#define BT_OS_MEMORY

#include "store.hpp"

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
		Memory()
			: Store() {};

		/**
		 * CTOR
		 * Any number of words.
		 */
		Memory(int numWords)
			: Store(numWords) {};
};

#endif
