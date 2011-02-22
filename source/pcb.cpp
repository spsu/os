#include <iostream>
#include <sstream>
#include "pcb.hpp"

using namespace std;

string Pcb::toString()
{
	stringstream s;

	s << "PCB <";
	s << "pri: " << priority << ", ";
	s << "start: " << diskInstructionsStart << ", ";
	s << "len: " << diskInstructionsLimit;
	s << ">";

	return s.str();
}
