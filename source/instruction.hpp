#ifndef BT_OS_INSTRUCTION
#define BT_OS_INSTRUCTION

#include <map>
#include <boost/tuple/tuple.hpp>
#include "types.hpp"

using namespace std;
using namespace boost;

/**
 * Types of Instruction Format.
 */
enum Format
{
	FORMAT_ARITHMETIC,
	FORMAT_COND_BRANCH_AND_IMM,
	FORMAT_UNCOND_JUMP,
	FORMAT_IO,
	FORMAT_UNKNOWN
};

typedef map<int, tuple<Format, string>> FormatMap;

/**
 * Opcodes
 */
enum Opcode
{
	OPCODE_RD,	// 00	I/O	Read
	OPCODE_WR,	// 01	I/O Write
	OPCODE_ST,	// 02	I	Store reg contents into an addr 
	OPCODE_LW,	// 03	I	Load addr contents into a reg
	OPCODE_MOV,	// 04	R	Transfer reg contents to another reg
	OPCODE_ADD,	// 05	R	Add two S-regs and store in D-reg
	OPCODE_SUB,	// 06	R	Subtract two S-regs and store in D-reg
	OPCODE_MUL,	// 07	R	Multiply two S-regs and store in D-reg
	OPCODE_DIV,	// 08	R	Divide two S-regs and store in D-reg
	OPCODE_AND,	// 09	R	AND two S-regs and store into D-reg
	OPCODE_OR,	// 0A	R	OR two S-regs and store into D-reg
	OPCODE_MOVI,// 0B	I	Transfer addr/data direct to reg			***
	OPCODE_ADDI,// 0C	I	Add data direct to reg contents
	OPCODE_MULI,// 0D	I	Multiply data direct to reg contents
	OPCODE_DIVI,// OE	I	Divide data direct to reg contents
	OPCODE_LDI,	// 0F	I	Load data/addr direct to reg contents		***
	OPCODE_SLT,	// 10	R	If S-reg1 < S-reg2, D-reg=1 else D-reg=0
	OPCODE_SLTI,// 11	I	If S-reg1 < data, D-reg=1 else D-reg=0	
	OPCODE_HLT,	// 12	I	Logical end of program!
	OPCODE_NOP,	// 13	-	No Op; move to next instr.
	OPCODE_JMP,	// 14	J	Jump to addr	
	OPCODE_BEQ,	// 15	I	If B-reg == D-reg, Branch to addr
	OPCODE_BNE,	// 16	I	If B-reg != D-reg, Branch to addr
	OPCODE_BEZ,	// 17	I	If D??-reg == 0, Branch to addr
	OPCODE_BNZ,	// 18	I	If B-reg != 0, Branch to addr
	OPCODE_BGZ,	// 19	I	If B-reg > 0, Branch to addr
	OPCODE_BLZ,	// 1A?	I	If B-reg < 0, Branch to addr
	OPCODE_UNKNOWN	// SPECIAL CASE
};

typedef map<int, tuple<Opcode, string>> OpcodeMap;

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
		Format format() const;
		string formatStr() const;

		/**
		 * Get the opcode.
		 */
		Opcode opcode() const;
		string opcodeStr() const;

		/**
		 * Get bits indicating various registers. 
		 * Only return meaningful data in the correct semantic context, 
		 * ie. must be used with the correct instruction format.
		 */
		int sReg1() const; // Arithmetic format (source register)
		int sReg2() const; // Arithmetic format (source register)
		int bReg() const;  // Conditional/Immediate format (base register)
		int reg1() const;  // IO format
		int reg2() const;  // IO format

		/**
		 * Get the 4-bit destination register.
		 * 	- bits 17-20 are used in Arithmetic format instructions.
		 * 	- bits 13-16 are used in Conditional/Immediate format.
		 * 	- returns -1 for other formats
		 */
		int dReg() const;

		/**
		 * Return the last 16 or 24 bits of the instruction.
		 * 	- 16 bits are returned in Conditional and I/O formats.
		 * 	- 24 bits are returned in Jump format
		 * 	- returns -1 for other formats
		 */
		int address() const;
		
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
		 * Opcode and Format maps
		 * Maps <int> to tuple<Opcode|Format, string abbreviation>
		 */
		static const OpcodeMap OPCODE_MAP;
		static const FormatMap FORMAT_MAP;

		/**
		 * Function to initialize map
		 */
		static const OpcodeMap initOpcodeMap();
		static const FormatMap initFormatMap();
};

#endif
