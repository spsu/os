#include <iostream>
#include <sstream>
#include "cpu.hpp"
#include "pcb.hpp"
#include "memory.hpp"
#include "instruction.hpp"
#include "processlist.hpp"

using namespace std;

int Cpu::counter = 0;

Cpu::Cpu(Memory* r) :
	pc(0),
	regs(16),
	cache(28),
	process(0), // TODO: Rename 'pcb'
	processList(0),
	ownsProcessList(true),
	ram(r),
	id(-1),
	readCount(0),
	writeCount(0),
	printDebug(false)
{
	processList = new ProcessList();
	id = counter;
	counter++;
}

Cpu::Cpu(Memory* r, ProcessList* pList) :
	pc(0),
	regs(16),
	cache(28),
	process(0), // TODO: Rename 'pcb'
	processList(pList),
	ownsProcessList(false),
	ram(r),
	id(-1),
	readCount(0),
	writeCount(0),
	printDebug(false)
{
	id = counter;
	counter++;
}

Cpu::~Cpu()
{
	if(ownsProcessList) {
		delete processList;
	}
}

// XXX: One execution cycle
void Cpu::execute() 
{
	Instruction i;

	if(!process) {
		// No process assigned to execute. 
		return;
	}

	i = Instruction(cache[pc]);

	switch(i.opcode()) 
	{
		// Read contents of input buffer into accumulator [IO]
		case OPCODE_RD:
			ram->acquire();
			regs[i.reg1()] = ram->get(effectiveAddress(
										(i.reg2()) ?
											regs[i.reg2()] :
											i.address()));
			ram->release();
			readCount++;
			break;

		// Writes contents of accumulator into output buffer [IO]
		case OPCODE_WR:
			ram->acquire();
			ram->set(effectiveAddress(
						(i.reg2())?
							regs[i.reg2()] : 
							i.address()), 
					regs[i.reg1()]);
			ram->release();
			writeCount++;
			break;

		// Stores content of a register into an address [I]
		case OPCODE_ST:
			ram->acquire();
			ram->set(effectiveAddress(regs[i.dReg()]), regs[i.bReg()]);
			ram->release();
			writeCount++;
			break;

		// Loads the content of an address into a register [I]
		case OPCODE_LW:
			ram->acquire();
			regs[i.dReg()] = ram->get(effectiveAddress(regs[i.bReg()]));
			ram->release();
			readCount++;
			break;

		// Transfer contents of one register into another [R]
		case OPCODE_MOV:
			regs[i.sReg1()] = regs[i.sReg2()];
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
		// XXX/TODO: Correct?
		case OPCODE_SLTI:
			regs[i.dReg()] = (regs[i.bReg()] < (unsigned int)i.address())? 1 : 0;
			break;

		// Halt, logical end of program
		case OPCODE_HLT:
			process->acquire();
			process->state = STATE_TERM_ON_CPU;
			process->release();
			if(printDebug) {
				cout << "[CPU] Process " << process->id << " finished.\n";
			}
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

	// XXX/TODO DEBUG
	//printRegs();
	//cout << endl;

	pc++;
}

bool Cpu::isComplete() const
{
	return (!process || process->state == STATE_TERM_ON_CPU);
}

void Cpu::printRegs() const
{
	for(unsigned int i = 0; i < regs.size(); i++) {
		//cout << "Reg[" << i << "] = " << regs.get(i) << endl;
		cout << "R[" << i << "] = " << regs.get(i) << ",  ";
	}
	cout << "PC = " << pc << endl;
}

word Cpu::getReg(int reg) const
{
	// XXX: No bounds checking!
	return regs.get(reg);
}

string Cpu::toString() const
{
	stringstream s;

	s << "CPU <";
	s << "id: " << id << ", ";
	if(isComplete()) {
		s << "not running";
	} 
	else {
		s << "running process #";
		s << process->id;
	}
	s << ">";

	return s.str();
}

unsigned int Cpu::effectiveAddress(unsigned int logical, 
		bool convert) const
{
	if (!process) {
		cout << "Cannot use Effective Address with no process!\n";
		return -1;
	}
	
	if(convert) {
		// Dividing converts from per-byte addressing 
		// into per-word addressing.
		return logical / 4 + process->ramPos.jobStart;
	}
	return process->ramPos.jobStart + logical;
}

// Only needs to be called by dispatcher.
void Cpu::clear()
{
	pc = 0;
	process = 0;
	readCount= 0;
	writeCount= 0;

	regs.reset();
	cache.reset();
}

