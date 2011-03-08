#include <iostream>
#include "cpu.hpp"
#include "pcb.hpp"
#include "instruction.hpp"

Cpu::Cpu() :
	registers(16),
	cache(28),
	process(0)
{
	cout << "Registers size: " << registers.size() << endl;
}

void Cpu::execute()
{
	Instruction instr; // TODO/XXX -- obviously this isn't coming from anywhere yet!!!

	switch(instr.opcode()) 
	{
		case OPCODE_RD:
			// Read
			break;
		case OPCODE_WR:
			// Write
			break;
		case OPCODE_ST:
			// Store
			break;
		case OPCODE_LW:
			// Load
			break;
		case OPCODE_MOV:
			// Move
			break;
		case OPCODE_ADD:
			// Add
			break;
		case OPCODE_SUB:
			// Subtract
			break;
		case OPCODE_MUL:
			// Multipy
			break;
		case OPCODE_DIV:
			// Divide
			break;
		case OPCODE_AND:
			// AND
			break;
		case OPCODE_OR:
			// OR
			break;
		case OPCODE_MOVI:
			// Move immediate
			break;
		case OPCODE_ADDI:
			// Add immediate
			break;
		case OPCODE_MULI:
			// Multiply immediate
			break;
		case OPCODE_DIVI:
			// Divide immediate
			break;
		case OPCODE_LDI:
			// Load immediate
			break;
		case OPCODE_SLT:
			// Set less than
			break;
		case OPCODE_SLTI:
			// Set less than immediate
			break;

		// Halt, logical end of program
		case OPCODE_HLT:
			process->finished = true;
			return; // XXX: Or break?

		// No-op, do nothing
		case OPCODE_NOP:
			break;

		case OPCODE_JMP:
			// Jump
			break;
		case OPCODE_BEQ:
			// Branch if equal
			break;
		case OPCODE_BNE:
			// Branch if not equal
			break;
		case OPCODE_BEZ:
			// Branch if equal zero
			break;
		case OPCODE_BNZ:
			// Branch if not equal zero
			break;
		case OPCODE_BGZ:
			// Branch if greater than zero
			break;
		case OPCODE_BLZ:
			// Branch if less than zero
			break;
		case OPCODE_UNKNOWN:
		default:
			// Unknown / error state
			break;
	}
	pc++;
}
