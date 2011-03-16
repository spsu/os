#ifndef BT_OS_STORE
#define BT_OS_STORE

#include <vector>
#include <string>
#include "types.hpp"

using namespace std;

/**
 * Store -- stores a set number of 32 bit 'words'. 
 * Registers, Caches, Memory, and Disk are all implemented through
 * the Store class, either directly or through subclasses.
 * TODO: Better Documentation.
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
		 * Empty the entire memory store.
		 * TODO: Disable functionality from working in Memory.
		 */
		void reset();

		/**
		 * String-formatted memory
		 * Good for debugging.
		 */
		string toString() const;

	protected:
		/**
		 * Memory space.
		 */
		vector<word> words;

		/**
		 * Marks each address as being allocated or not.
		 * Only utilized in Memory subclasses. 
		 * TODO: Move to Memory class. Will require virtual
		 * methods though.
		 */
		vector<bool> allocated;
};

#endif
