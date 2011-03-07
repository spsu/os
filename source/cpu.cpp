#include <iostream>
#include "cpu.hpp"

Cpu::Cpu() :
	registers(16),
	cache(100) // TODO: Figure out a good size for this
{
	cout << "Registers size: " << registers.size() << endl;
}

void Cpu::execute()
{


}
