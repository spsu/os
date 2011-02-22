#ifndef BT_OS_PCB
#define BT_OS_PCB

/**
 * TODO: Documentation.
 */

struct Pcb 
{
	// TODO: CTORs
	Pcb()
		: priority(0),
		diskInstructionsStart(0),
		diskInstructionsLimit(0),
		diskDataStart(0),
		diskDataLimit(0) {};

	/**
	 * Debug method
	 */
	void print(); // TODO: toString would be better

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
