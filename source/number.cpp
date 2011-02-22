#include <iostream>
#include <sstream>

#include "number.hpp"

using namespace std;

word hex_to_dec(string hexStr)
{
	word ret(0);
	istringstream(hexStr) >> hex >> ret;
	return ret;
}


