#include <iostream>
#include <sstream>
#include <algorithm> // reverse()

#include "number.hpp"

using namespace std;

word hex_to_dec(string hexStr)
{
	word ret(0);
	istringstream(hexStr) >> hex >> ret;
	return ret;
}

// Based on a simple algorithm found at:
// http://www.cplusplus.com/forum/general/10898
string dec_to_bin(unsigned int dec, bool zerofill, bool splitBytes)
{
	string ret = "";

	if(zerofill) {
		unsigned int i = 31; // Zerofill assumes 32 bits
		ret = string(32, '0');
		while(dec) {
			ret[i] = (dec & 1) + '0';
			dec >>= 1;
			i--;
		}
	}
	else {
		while(dec) {
			 ret.push_back((dec & 1) + '0');
			 dec >>= 1;
		}
		if (ret.empty())
			ret = "0";
		else
			reverse(ret.begin(), ret.end());
	}

	if(!splitBytes) {
		return ret;
	}

	// Add spaces every byte.
	unsigned int sz = ret.size();
	unsigned int numBytes = sz / 8;

	for(unsigned int i = 0; i < numBytes; i++) {
		int pos = sz - ((i+1)*8);
		if(pos <= 0) 
			break;
		ret.insert(pos, " ");	
	}

	return ret;
}


