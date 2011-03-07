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
		return INSTR_UNKNOWN;
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

string Instruction::toString() const
{
	stringstream s;

	// TODO: Output will vary based on the type of instruction. 
	// Perhaps we should output binary first for this reason.
	
	s << "Instr <";
	s << dec_to_bin(instr, true, true) << "; "; // zerofilled w/ spaces 
	s << "f: " << formatStr() << " \t";
	s << "op: " << opcodeStr() << " ";
	// TODO: Regs/Values
	s << ">";

	return s.str();
}

// Static initilization of map
const OpcodeMap Instruction::initOpcodeMap()
{
	OpcodeMap m;

	// XXX: Spaces in strings are for formatting
	m[0x00] = make_tuple(INSTR_RD, "rd  ");
	m[0x01] = make_tuple(INSTR_WR, "wr  ");
	m[0x02] = make_tuple(INSTR_ST, "st  "); 
	m[0x03] = make_tuple(INSTR_LW, "lw  ");
	m[0x04] = make_tuple(INSTR_MOV, "mov ");
	m[0x05] = make_tuple(INSTR_ADD, "add ");
	m[0x06] = make_tuple(INSTR_SUB, "sub ");
	m[0x07] = make_tuple(INSTR_MUL, "mul ");
	m[0x08] = make_tuple(INSTR_DIV, "div ");
	m[0x09] = make_tuple(INSTR_AND, "AND ");
	m[0x0A] = make_tuple(INSTR_OR, "OR  ");
	m[0x0B] = make_tuple(INSTR_MOVI, "movi");
	m[0x0C] = make_tuple(INSTR_ADDI, "addi");
	m[0x0D] = make_tuple(INSTR_MULI, "muli");
	m[0x0E] = make_tuple(INSTR_DIVI, "divi");
	m[0x0F] = make_tuple(INSTR_LDI, "ldi ");
	m[0x10] = make_tuple(INSTR_SLT, "slt ");
	m[0x11] = make_tuple(INSTR_SLTI, "slti");
	m[0x12] = make_tuple(INSTR_HLT, "HLT ");
	m[0x13] = make_tuple(INSTR_NOP, "NOP ");
	m[0x14] = make_tuple(INSTR_JMP, "jmp ");
	m[0x15] = make_tuple(INSTR_BEQ, "beq ");
	m[0x16] = make_tuple(INSTR_BNE, "bne ");
	m[0x17] = make_tuple(INSTR_BEZ, "bez ");
	m[0x18] = make_tuple(INSTR_BNZ, "bnz ");
	m[0x19] = make_tuple(INSTR_BGZ, "bgz ");
	m[0x1A] = make_tuple(INSTR_BLZ, "blz "); // XXX: Is the order right??? 

	return m;
}

const FormatMap Instruction::initFormatMap()
{
	FormatMap m;

	m[0x0] = make_tuple(FORMAT_ARITHMETIC, "arith");
	m[0x1] = make_tuple(FORMAT_COND_BRANCH_AND_IMM, "cnd/imm");
	m[0x2] = make_tuple(FORMAT_UNCOND_JUMP, "jump"); 
	m[0x3] = make_tuple(FORMAT_IO, "i/o "); // XXX: Space is for formatting

	return m;
}

