#include <iostream>
#include "instruction.hpp"

using namespace std;

InstructionFormatType Instruction::format()
{
	return UNKNOWN;
}

void Instruction::print()
{
	cout << "Instr: " << instr ;

	unsigned int form = instr >> 30;

	cout << ", Form: " << form << ", ";


}
