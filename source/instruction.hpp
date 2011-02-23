#ifndef BT_OS_INSTRUCTION
#define BT_OS_INSTRUCTION

#include <map>
#include "types.hpp"

using namespace std;

/**
 * Types of Instruction Format.
 */
enum InstructionFormat
{
	FORMAT_ARITHMETIC,
	FORMAT_COND_BRANCH_AND_IMM,
	FORMAT_UNCOND_JUMP,
	FORMAT_IO,
	FORMAT_UNKNOWN
};

/**
 * Opcodes
 */
enum Opcode
{
	INSTR_RD,	// 00	I/O	Read
	INSTR_WR,	// 01	I/O Write
	INSTR_ST,	// 02	I	Store reg contents into an addr 
	INSTR_LW,	// 03	I	Load addr contents into a reg
	INSTR_MOV,	// 04	R	Transfer reg contents to another reg
	INSTR_ADD,	// 05	R	Add two S-regs and store in D-reg
	INSTR_SUB,	// 06	R	Subtract two S-regs and store in D-reg
	INSTR_MUL,	// 07	R	Multiply two S-regs and store in D-reg
	INSTR_DIV,	// 08	R	Divide two S-regs and store in D-reg
	INSTR_AND,	// 09	R	AND two S-regs and store into D-reg
	INSTR_OR,	// 0A	R	OR two S-regs and store into D-reg
	INSTR_MOVI,	// 0B	I	Transfer addr/data direct to reg			***
	INSTR_ADDI,	// 0C	I	Add data direct to reg contents
	INSTR_MULI,	// 0D	I	Multiply data direct to reg contents
	INSTR_DIVI,	// OE	I	Divide data direct to reg contents
	INSTR_LDI,	// 0F	I	Load data/addr direct to reg contents		***
	INSTR_SLT,	// 10	R	If S-reg1 < S-reg2, D-reg=1 else D-reg=0
	INSTR_SLTI,	// 11	I	If S-reg1 < data, D-reg=1 else D-reg=0	
	INSTR_HLT,	// 12	I	Logical end of program!
	INSTR_NOP,	// 13	-	No Op; move to next instr.
	INSTR_JMP,	// 14	J	Jump to addr	
	INSTR_BEQ,	// 15	I	If B-reg == D-reg, Branch to addr
	INSTR_BNE,	// 16	I	If B-reg != D-reg, Branch to addr
	INSTR_BEZ,	// 17	I	If D??-reg == 0, Branch to addr
	INSTR_BNZ,	// 18	I	If B-reg != 0, Branch to addr
	INSTR_BGZ,	// 19	I	If B-reg > 0, Branch to addr
	INSTR_BLZ,	// 1A?	I	If B-reg < 0, Branch to addr
	INSTR_UNKNOWN	// SPECIAL CASE
};

/**
 * This class provides instruction decoding.
 */
class Instruction
{
	public:
		/**
		 * Default CTOR.
		 * (Useless)
		 */
		Instruction()
			: instr(0),
			binaryInstr("") {};

		/**
		 * CTOR: Specify instruction
		 */
		Instruction(word instruction);

		/**
		 * Get the type of format.
		 */
		InstructionFormat format() const;

		/**
		 * Get the opcode.
		 */
		Opcode opcode() const;

		/**
		 * For Debug
		 */
		string toString() const;
		
		// TODO: Return as "bytes", ie: 00101101 10111100 0100001 11010001
		// TODO: Binary conversion
		//string binString() const; 

	private:
		/**
		 * The instruction.
		 */
		word instr;

		/**
		 * The instruction as a binary string.
		 */
		string binaryInstr;

		/**
		 * Map of Opcode: Instruction
		 */
		static const map<int, Opcode> OPCODE_MAP;

		/**
		 * Function to initialize map
		 */
		static const map<int, Opcode> initOpcodeMap();
};

#endif
