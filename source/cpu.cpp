#include <iostream>
#include "cpu.hpp"

Cpu::Cpu() :
	registers(16),
	cache(28)
{
	cout << "Registers size: " << registers.size() << endl;
}

void Cpu::execute()
{


}
