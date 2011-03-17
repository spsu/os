#ifndef BT_OS_TYPES
#define BT_OS_TYPES

#include <cstdint>

// XXX: This file contains simple types.

/**
 * Words are 32 bits, fixed size.
 */
typedef uint32_t word;

/**
 * Memory positions.
 * Used for accounting in PCBs.
 */
struct Position 
{
	int jobStart;
	int dataStart;

	Position() : jobStart(0), dataStart(0) {};
};

#endif
