#include <iostream>
#include <sstream>
#include "instruction.hpp"
#include "number.hpp"

using namespace std;
using namespace boost;

// Initialize static const maps 
const OpcodeMap Instruction::OPCODE_MAP = initOpcodeMap();
const FormatMap Instruction::FORMAT_MAP = initFormatMap();

Instruction::Instruction(word instruction)
	: instr(instruction),
	binaryInstr("")
{
	// zerofill, but do not insert spaces.
	binaryInstr = dec_to_bin(instruction, true, false);
}

Format Instruction::format() const
{
	FormatMap::const_iterator it;

	it = FORMAT_MAP.find(bin_to_dec(binaryInstr.substr(0, 2)));
	
	// TODO: Confusing to have FORMAT_MAP and FORMAT_* names
	if(it == FORMAT_MAP.end()) { 
		return FORMAT_UNKNOWN;
	}
	return it->second.get<0>();
}

string Instruction::formatStr() const
{
	FormatMap::const_iterator it;

	it = FORMAT_MAP.find(bin_to_dec(binaryInstr.substr(0, 2)));
	
	// TODO: Confusing to have FORMAT_MAP and FORMAT_* names
	if(it == FORMAT_MAP.end()) { 
		return "Unknown";
	}
	return it->second.get<1>();
}

Opcode Instruction::opcode() const
{
	OpcodeMap::const_iterator it;

	it = OPCODE_MAP.find(bin_to_dec(binaryInstr.substr(2, 6)));
	if(it == OPCODE_MAP.end()) {
		return OPCODE_UNKNOWN;
	}
	return it->second.get<0>();
}

string Instruction::opcodeStr() const
{
	OpcodeMap::const_iterator it;

	it = OPCODE_MAP.find(bin_to_dec(binaryInstr.substr(2, 6)));
	if(it == OPCODE_MAP.end()) {
		return "Unknown";
	}
	return it->second.get<1>();
}

int Instruction::sReg1() const
{
	if(format() != FORMAT_ARITHMETIC) {
		return -1;
	}
	return bin_to_dec(binaryInstr.substr(8, 4));
}

int Instruction::sReg2() const
{
	if(format() != FORMAT_ARITHMETIC) {
		return -1;
	}
	return bin_to_dec(binaryInstr.substr(12, 4));
}

int Instruction::bReg() const
{
	if(format() != FORMAT_COND_BRANCH_AND_IMM) {
		return -1;
	}
	return bin_to_dec(binaryInstr.substr(8, 4));
}

int Instruction::reg1() const
{
	if(format() != FORMAT_IO) {
		return -1;
	}
	return bin_to_dec(binaryInstr.substr(8, 4));
}

int Instruction::reg2() const
{
	if(format() != FORMAT_IO) {
		return -1;
	}
	return bin_to_dec(binaryInstr.substr(12, 4));
}

int Instruction::dReg() const
{
	switch(format()) {
		case FORMAT_ARITHMETIC:
			return bin_to_dec(binaryInstr.substr(16, 4));

		case FORMAT_COND_BRANCH_AND_IMM:
			return bin_to_dec(binaryInstr.substr(12, 4));

		default:
			break;
	}
	return -1;
}

int Instruction::address() const
{
	switch(format()) {
		case FORMAT_COND_BRANCH_AND_IMM:
		case FORMAT_IO:
			return bin_to_dec(binaryInstr.substr(16, 16));

		case FORMAT_UNCOND_JUMP:
			return bin_to_dec(binaryInstr.substr(8, 24));

		default:
			break;
	}
	return -1;
}

string Instruction::toString() const
{
	stringstream s;

	// TODO: Output will vary based on the type of instruction. 
	// Perhaps we should output binary first for this reason.
	
	s << "Instr <";
	s << dec_to_bin(instr, true, true) << "  "; // zerofilled w/ spaces 
	//s << "f: " << formatStr() << " \t";
	s << opcodeStr() << " ";
	s << "(" << formatStr() << ")  ";
	s << "";
	s << argStr();
	// TODO: Regs/Values
	s << ">";

	return s.str();
}

/**
 * Returns args as a string. 
 * Helps with debugging.
 */
string Instruction::argStr() const
{
	stringstream s;

	switch(format()) {
		case FORMAT_ARITHMETIC:
			s << "s: " << sReg1();
			s << ", ";
			s << "s: " << sReg2(); 
			s << ", ";
			s << "d: " << dReg();
			s << ", ";
			s << "addr: " << address();
			break;

		case FORMAT_COND_BRANCH_AND_IMM:
			s << "b: " << bReg();
			s << ", ";
			s << "d: " << dReg();
			s << ", ";
			s << "addr: " << address();
			break;

		case FORMAT_UNCOND_JUMP:
			s << "addr: " << address();
			break;

		case FORMAT_IO:
			s << "r: " << reg1();
			s << ", ";
			s << "r: " << reg2();
			s << ", ";
			s << "addr: " << address();
			break;

		default:
			s << "";
			break;
	}

	return s.str();
}

// Static initilization of map
const OpcodeMap Instruction::initOpcodeMap()
{
	OpcodeMap m;

	// XXX: Spaces in strings are for formatting
	m[0x00] = make_tuple(OPCODE_RD, "rd  ");
	m[0x01] = make_tuple(OPCODE_WR, "wr  ");
	m[0x02] = make_tuple(OPCODE_ST, "st  "); 
	m[0x03] = make_tuple(OPCODE_LW, "lw  ");
	m[0x04] = make_tuple(OPCODE_MOV, "mov ");
	m[0x05] = make_tuple(OPCODE_ADD, "add ");
	m[0x06] = make_tuple(OPCODE_SUB, "sub ");
	m[0x07] = make_tuple(OPCODE_MUL, "mul ");
	m[0x08] = make_tuple(OPCODE_DIV, "div ");
	m[0x09] = make_tuple(OPCODE_AND, "AND ");
	m[0x0A] = make_tuple(OPCODE_OR, "OR  ");
	m[0x0B] = make_tuple(OPCODE_MOVI, "movi");
	m[0x0C] = make_tuple(OPCODE_ADDI, "addi");
	m[0x0D] = make_tuple(OPCODE_MULI, "muli");
	m[0x0E] = make_tuple(OPCODE_DIVI, "divi");
	m[0x0F] = make_tuple(OPCODE_LDI, "ldi ");
	m[0x10] = make_tuple(OPCODE_SLT, "slt ");
	m[0x11] = make_tuple(OPCODE_SLTI, "slti");
	m[0x12] = make_tuple(OPCODE_HLT, "HLT ");
	m[0x13] = make_tuple(OPCODE_NOP, "NOP ");
	m[0x14] = make_tuple(OPCODE_JMP, "jmp ");
	m[0x15] = make_tuple(OPCODE_BEQ, "beq ");
	m[0x16] = make_tuple(OPCODE_BNE, "bne ");
	m[0x17] = make_tuple(OPCODE_BEZ, "bez ");
	m[0x18] = make_tuple(OPCODE_BNZ, "bnz ");
	m[0x19] = make_tuple(OPCODE_BGZ, "bgz ");
	m[0x1A] = make_tuple(OPCODE_BLZ, "blz "); // Not a mistake! 

	return m;
}

const FormatMap Instruction::initFormatMap()
{
	FormatMap m;

	m[0x0] = make_tuple(FORMAT_ARITHMETIC, "ath");
	m[0x1] = make_tuple(FORMAT_COND_BRANCH_AND_IMM, "c/i");
	m[0x2] = make_tuple(FORMAT_UNCOND_JUMP, "jmp"); 
	m[0x3] = make_tuple(FORMAT_IO, "i/o");

	return m;
}

