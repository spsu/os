#include <iostream>
#include "instruction.hpp"

using namespace std;

InstructionFormatType Instruction::format() const
{
	return UNKNOWN; // TODO
}

void Instruction::print() const
{
	cout << "Instr: " << instr ;

	unsigned int form = instr >> 30;

	cout << ", Form: " << form << ", ";


}
