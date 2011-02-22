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
		InstructionFormatType format();

		/**
		 * For Debug
		 */
		void print();

	private:
		/**
		 * The instruction.
		 */
		word instr;
};

#endif
