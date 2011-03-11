#include <iostream>
#include "cpu.hpp"
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"

Cpu::Cpu(Memory* r) :
	pc(0),
	regs(16),
	cache(28),
	process(0), // TODO: Rename 'pcb'
	ram(r)
{
	// XXX: Blank for now
}

void Cpu::execute() // XXX: One execution cycle
{
	Instruction i;
	int r = 0;
	int val = 0;

	i = Instruction(cache[pc]);

	// XXX XXX XXX XXX
	// Instruction set uses byte addressing.
	// 		* Memory get/set locations
	// 		* Branching (pc = data)
	// I'm using word addressing. 
	// I really don't like this mismatch. 
	// XXX XXX XXX XXX
	
	switch(i.opcode()) 
	{
		// Read contents of input buffer into accumulator [IO]
		// TODO: Need indirect addressing
		// TODO: Need DMA channel
		case OPCODE_RD:
			r = i.reg2(); // XXX: Should I check address != 0 instead?
			if(r) {
				val = ram->get(regs[r] / 4);
			}
			else {
				val = ram->get(i.address() / 4);
			}
			regs[i.reg1()] = val;
			break;

		// Writes contents of accumulator into output buffer [IO]
		// TODO: Need indirect addressing
		// TODO: Need DMA channel
		case OPCODE_WR:
			ram->set(i.address() / 4, regs[i.reg1()]);
			break;

		// Stores content of a register into an address [I]
		// TODO: Need indirect addressing
		// TODO: Need DMA channel
		case OPCODE_ST:
			ram->set(regs[i.dReg()] / 4, regs[i.bReg()]);	
			break;

		// Loads the content of an address into a register [I]
		// XXX: How is this different than RD?
		// TODO: Need indirect addressing
		// TODO: Need DMA channel
		case OPCODE_LW:
			regs[i.dReg()] = ram->get(regs[i.bReg()] / 4);
			break;

		// Transfer contents of one register into another [R]
		// TODO TODO TODO TODO TODO TODO NOT DONE
		case OPCODE_MOV:
			cout << "TODO: MOV" << endl;
			break;

		// Add content of two S-regs into D-reg [R]
		case OPCODE_ADD:
			regs[i.dReg()] = regs[i.sReg1()] + regs[i.sReg2()];
			break;

		// Subtracts content of two S-regs into D-reg [R]
		case OPCODE_SUB:
			regs[i.dReg()] = regs[i.sReg1()] - regs[i.sReg2()];
			break;

		// Multiplies content of two S-regs into D-reg [R]
		case OPCODE_MUL:
			regs[i.dReg()] = regs[i.sReg1()] * regs[i.sReg2()];
			break;

		// Divides content of two S-regs into D-reg [R]
		case OPCODE_DIV:
			regs[i.dReg()] = regs[i.sReg1()] / regs[i.sReg2()];
			break;

		// Logical AND of two S-regs into D-reg [R] 
		case OPCODE_AND:
			regs[i.dReg()] = regs[i.sReg1()] & regs[i.sReg2()];
			break;

		// Logical OR of two S-regs into D-reg [R] 
		case OPCODE_OR:
			regs[i.dReg()] = regs[i.sReg1()] | regs[i.sReg2()];
			break;

		// Transfers address/data directly into a register [I]
		case OPCODE_MOVI:
			regs[i.dReg()] = i.address();
			break;

		// Adds data directly to the content of a register [I]
		case OPCODE_ADDI:
			regs[i.dReg()] += i.address();
			break;

		// Multiplies data directly to the content of a register [I]
		case OPCODE_MULI:
			regs[i.dReg()] *= i.address();
			break;

		// Divides data directly to the content of a register [I]
		case OPCODE_DIVI:
			regs[i.dReg()] /= i.address();
			break;

		// Loads data/address directly into a register [I]
		case OPCODE_LDI:
			regs[i.dReg()] = i.address();
			break;

		// Set less than; (sReg1 < sReg2)? dReg = 1 : dReg = 0 [R]
		case OPCODE_SLT:
			regs[i.dReg()] = (regs[i.sReg1()] < regs[i.sReg2()])? 1 : 0;
			break;

		// Set less than immediate; (sReg1 < addr/data) : dReg = 1 : 0 [I]
		case OPCODE_SLTI:
			regs[i.dReg()] = (regs[i.bReg()] < (unsigned int)i.address())? 1 : 0; // XXX/TODO: Correct?
			break;

		// Halt, logical end of program
		case OPCODE_HLT:
			process->finished = true;
			return;

		// No-op, do nothing
		case OPCODE_NOP:
			break;

		// Jump to address
		case OPCODE_JMP:
			pc = i.address() / 4; // TODO/XXX: Is this correct?
			return;

		// Branch to address when B-reg == D-reg
		case OPCODE_BEQ:
			if(regs[i.bReg()] == regs[i.dReg()]) {
				pc = i.address() / 4;
				return;
			}
			break;

		// Branch to address when B-reg != D-reg
		case OPCODE_BNE:
			if(regs[i.bReg()] != regs[i.dReg()]) {
				pc = i.address() / 4;
				return;
			}
			break;

		// Branch to address when D-reg (TODO/XXX:????) == 0
		case OPCODE_BEZ:
			if(regs[i.dReg()] == 0) {
				pc = i.address() / 4;
				return;
			}
			break;

		// Branch to address when B-reg != 0
		case OPCODE_BNZ:
			if(regs[i.bReg()] != 0) {
				pc = i.address() / 4;
				return;
			}
			break;

		// Branch to address when B-reg > 0
		case OPCODE_BGZ:
			if(regs[i.bReg()] > 0) {
				pc = i.address() / 4;
				return;
			}
			break;

		// Branch to address when B-reg < 0
		case OPCODE_BLZ:
			if(regs[i.bReg()] < 0) {
				pc = i.address() / 4;
				return;
			}
			break;

		// Unknown instruction / error state.
		case OPCODE_UNKNOWN:
		default:
			cout << "Unknown instruction in Cpu::execute()." << endl;
			break;
	}
	pc++;
}

bool Cpu::isComplete() const
{
	return (process && process->finished);
}

void Cpu::printRegs() const
{
	for(unsigned int i = 0; i < regs.size(); i++) {
		cout << "Reg[" << i << "] = " << regs.get(i) << endl;
	}
	cout << "PC = " << pc << endl;
}

