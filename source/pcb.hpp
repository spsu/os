#ifndef BT_OS_PCB
#define BT_OS_PCB

#include <string>

/**
 * TODO: Documentation.
 */

class Memory;

class Pcb 
{
	public:

		// TODO: CTORs

		/**
		 * Default CTOR.
		 */
		Pcb()
			: priority(0),
			diskInstructionsStart(0),
			diskInstructionsLimit(0),
			diskDataStart(0),
			diskDataLimit(0) {};

		/**
		 * Debug methods
		 */
		std::string toString() const;
		void printCode(const Memory& mem) const;
		//void printData(const Memory& mem);

	private:
		/**
		 * Data Members
		 */
		int priority;

		// TODO: These are a WIP 
		int diskInstructionsStart;
		int diskInstructionsLimit;
		int diskDataStart;
		int diskDataLimit;
};

#endif
