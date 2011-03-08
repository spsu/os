#ifndef BT_OS_PCB
#define BT_OS_PCB

#include <string>
#include "types.hpp"
#include "store.hpp"

/**
 * TODO: Documentation.
 */

class Memory;

class Pcb 
{
	public:
		/**
		 * Default CTOR.
		 */
		Pcb();

		/**
		 * String representation of PCB 
		 */
		std::string toString() const;

		/**
		 * Process debugging
		 */
		void printProg(const Memory& mem) const;

		// XXX: Data members are *public*
		
		/**
		 * Job priority
		 */
		int priority;

		/**
		 * Memory map
		 */
		int jobStart;
		int jobLength;
		int dataStart;
		int dataLength;
		int dataInLength;
		int dataOutLength;
		int dataTempLength;

		/**
		 * CPU save state
		 */
		word pc;
		Store registers;
};

#endif
