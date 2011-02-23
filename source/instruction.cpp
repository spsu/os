#include <iostream>
#include "instruction.hpp"

using namespace std;

// Initialize static const map of opcodes
const map<unsigned int, Opcode> Instruction::OPCODE_MAP = initOpcodeMap();

InstructionFormat Instruction::format() const
{
	return UNKNOWN; // TODO
}

void Instruction::print() const
{
	cout << "Instr: " << instr ;

	unsigned int form = instr >> 30;

	cout << ", Form: " << form << ", ";
}

// Static initilization of map
map<unsigned int, Opcode> Instruction::initOpcodeMap() 
{
	map<unsigned int, Opcode> m;
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
	m[0x1A] = INSTR_BLZ; // XXX: ??? 
	return m;
}
