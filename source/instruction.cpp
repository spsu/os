#include <iostream>
#include <sstream>
#include "instruction.hpp"
#include "number.hpp"

using namespace std;

// Initialize static const map of opcodes
const map<int, Opcode> Instruction::OPCODE_MAP = initOpcodeMap();
const map<int, InstructionFormat> Instruction::INSTRUCTION_FORMAT_MAP
		= initInstructionFormatMap();

Instruction::Instruction(word instruction)
	: instr(instruction),
	binaryInstr("")
{
	// zerofill, but do not insert spaces.
	binaryInstr = dec_to_bin(instruction, true, false);
}

InstructionFormat Instruction::format() const
{
	// XXX: The following code works.
	/*switch(bin_to_dec(binaryInstr.substr(0, 2))) {
		case 0:
			return FORMAT_ARITHMETIC;	
		case 1:
			return FORMAT_COND_BRANCH_AND_IMM;
		case 2:
			return FORMAT_UNCOND_JUMP;	
		case 3:
			return FORMAT_IO;
	}
	return FORMAT_UNKNOWN;
	*/
	map<int, InstructionFormat>::const_iterator it;

	it = INSTRUCTION_FORMAT_MAP.find(bin_to_dec(binaryInstr.substr(0, 2)));

	if(it == INSTRUCTION_FORMAT_MAP.end()) {
		return FORMAT_UNKNOWN;
	}
	return it->second;
}

Opcode Instruction::opcode() const
{
	map<int, Opcode>::const_iterator it;

	it = OPCODE_MAP.find(bin_to_dec(binaryInstr.substr(2, 6)));

	if(it == OPCODE_MAP.end()) {
		return INSTR_UNKNOWN;
	}
	return it->second;
}

string Instruction::toString() const
{
	stringstream s;

	// TODO: Ugh, messy...
	static map<InstructionFormat, string> f;
	f[FORMAT_ARITHMETIC] = "arith";
	f[FORMAT_COND_BRANCH_AND_IMM] = "cond/imm";
	f[FORMAT_UNCOND_JUMP] = "jump";
	f[FORMAT_IO] = "i/o";
	f[FORMAT_UNKNOWN] = "unkn";

	// TODO: Output will vary based on the type of instruction. 
	// Perhaps we should output binary first for this reason.
	
	s << "Instr <";
	s << dec_to_bin(instr, true, true) << "; "; // zerofilled w/ spaces 
	s << "f: " << f[format()] << "\t";
	s << "op: " << opcode() << "\t";
	s << "op: ___\tregsOrVals: x, y, z"; // XXX/TODO: Idea only
	//s << "op: " << opcode() << ", "; 
	s << ">";

	return s.str();
}

// Static initilization of map
const map<int, Opcode> Instruction::initOpcodeMap()
{
	map<int, Opcode> m;
	m[0x00] = INSTR_RD;
	m[0x01] = INSTR_WR;
	m[0x02] = INSTR_ST;
	m[0x03] = INSTR_LW;
	m[0x04] = INSTR_MOV;
	m[0x05] = INSTR_ADD;
	m[0x06] = INSTR_SUB;
	m[0x07] = INSTR_MUL;
	m[0x08] = INSTR_DIV;
	m[0x09] = INSTR_AND;
	m[0x0A] = INSTR_OR;
	m[0x0B] = INSTR_MOVI;
	m[0x0C] = INSTR_ADDI;
	m[0x0D] = INSTR_MULI;
	m[0x0E] = INSTR_DIVI;
	m[0x0F] = INSTR_LDI;
	m[0x10] = INSTR_SLT;
	m[0x11] = INSTR_SLTI;
	m[0x12] = INSTR_HLT;
	m[0x13] = INSTR_NOP;
	m[0x14] = INSTR_JMP;
	m[0x15] = INSTR_BEQ;
	m[0x16] = INSTR_BNE;
	m[0x17] = INSTR_BEZ;
	m[0x18] = INSTR_BNZ;
	m[0x19] = INSTR_BGZ;
	m[0x1A] = INSTR_BLZ; // XXX: Is the order right??? 
	return m;
}

const map<int, InstructionFormat> Instruction::initInstructionFormatMap()
{
	map<int, InstructionFormat> m;
	m[0x0] = FORMAT_ARITHMETIC;	
	m[0x1] = FORMAT_COND_BRANCH_AND_IMM;
	m[0x2] = FORMAT_UNCOND_JUMP;	
	m[0x3] = FORMAT_IO;
	return m;
}

