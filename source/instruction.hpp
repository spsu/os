#ifndef BT_OS_INSTRUCTION
#define BT_OS_INSTRUCTION

#include "types.hpp"

/**
 * Types of Instruction Format.
 */
enum InstructionFormatType
{
	ARITHMETIC,
	COND_BRANCH_AND_IMM,
	UNCOND_JUMP,
	IO,
	UNKNOWN
};

/**
 * This class provides instruction decoding.
 */
class Instruction
{
	public:
		/**
		 * CTORs.
		 */
		Instruction()
			: instr(0) {};

		Instruction(word instruction)
			: instr(instruction) {};

		/**
		 * Get the type of format.
		 */
		InstructionFormatType format() const;

		/**
		 * For Debug
		 */
		void print() const;
		
		// TODO: Return as "bytes", ie: 00101101 10111100 0100001 11010001
		// TODO: Binary conversion
		//string binString() const; 

	private:
		/**
		 * The instruction.
		 */
		word instr;
};

#endif
