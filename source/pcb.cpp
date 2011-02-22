#include <iostream>
#include "pcb.hpp"

using namespace std;

// TODO: toString would be better.
void Pcb::print()
{
	cout << "PCB <"
		<< "pri: " << priority
		<< ", start: " << diskInstructionsStart
		<< ", len: " << diskInstructionsLimit
		<< ">";
}
