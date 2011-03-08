#include <iostream>
#include "cpu.hpp"
#include "pcb.hpp"
#include "instruction.hpp"

Cpu::Cpu() :
	regs(16),
	cache(28),
	process(0)
{
	cout << "Registers size: " << regs.size() << endl;
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
			// Transfer contents of one register into another [R]
			break;

		// Add content of two S-regs into D-reg [R]
		case OPCODE_ADD:
			regs[instr.dReg()] = regs[instr.sReg1()] + regs[instr.sReg2()];
			break;

		// Subtracts content of two S-regs into D-reg [R]
		case OPCODE_SUB:
			regs[instr.dReg()] = regs[instr.sReg1()] - regs[instr.sReg2()];
			break;

		// Multiplies content of two S-regs into D-reg [R]
		case OPCODE_MUL:
			regs[instr.dReg()] = regs[instr.sReg1()] * regs[instr.sReg2()];
			break;

		// Divides content of two S-regs into D-reg [R]
		case OPCODE_DIV:
			regs[instr.dReg()] = regs[instr.sReg1()] / regs[instr.sReg2()];
			break;

		// Logical AND of two S-regs into D-reg [R] 
		case OPCODE_AND:
			regs[instr.dReg()] = regs[instr.sReg1()] & regs[instr.sReg2()];
			break;

		// Logical OR of two S-regs into D-reg [R] 
		case OPCODE_OR:
			regs[instr.dReg()] = regs[instr.sReg1()] | regs[instr.sReg2()];
			break;

		// Transfers address/data directly into a register [I]
		case OPCODE_MOVI:
			regs[instr.bReg()] = instr.address(); // XXX/TODO: bReg() or dReg() ????
			break;

		// Adds data directly to the content of a register [I]
		case OPCODE_ADDI:
			regs[instr.bReg()] += instr.address(); // XXX/TODO: bReg() or dReg() ????
			break;

		// Multiplies data directly to the content of a register [I]
		case OPCODE_MULI:
			regs[instr.bReg()] *= instr.address(); // XXX/TODO: bReg() or dReg() ????
			break;

		// Divides data directly to the content of a register [I]
		case OPCODE_DIVI:
			regs[instr.bReg()] /= instr.address(); // XXX/TODO: bReg() or dReg() ????
			break;

		// Loads data/address directly into a register [I]
		case OPCODE_LDI:
			regs[instr.bReg()] = instr.address(); // XXX/TODO: bReg() or dReg() ????
			break;

		// Set less than; (sReg1 < sReg2)? dReg = 1 : dReg = 0 [R]
		case OPCODE_SLT:
			regs[instr.dReg()] = (instr.sReg1() < instr.sReg2())? 1 : 0; 
			break;

		// Set less than immediate; (sReg1 < addr/data) : dReg = 1 : 0 [I]
		case OPCODE_SLTI:
			regs[instr.dReg()] = (instr.bReg() < instr.address())? 1 : 0; // XXX/TODO: Correct?
			break;

		// Halt, logical end of program
		case OPCODE_HLT:
			process->finished = true;
			return; // XXX/TODO: Or break?

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
			// XXX/TODO: What do do?
			break;
	}
	pc++;
}
