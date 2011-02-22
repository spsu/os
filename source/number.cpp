#include <iostream>
#include <sstream>
#include <algorithm> // XXX: TEMPORARY

#include "number.hpp"

using namespace std;

word hex_to_dec(string hexStr)
{
	word ret(0);
	istringstream(hexStr) >> hex >> ret;
	return ret;
}

// Based on the concise algorithm found at
// http://www.cplusplus.com/forum/general/10898
string dec2binA(unsigned n)
{
    string res;

    while (n) {
        res.push_back((n & 1) + '0');
        n >>= 1;
    }

    if (res.empty())
        res = "0";
    else
        reverse(res.begin(), res.end());
 
   return res;
}


// Based on the concise algorithm found at
// http://www.cplusplus.com/forum/general/10898
string dec2binB(unsigned dec, bool zerofill, bool splitByte)
{
	string ret = string(32, '0'); // Zerofill.
	unsigned int i = 31;

	while (dec) {
		ret[i] = (dec & 1) + '0';
		dec >>= 1;
		i--;
	}

	return ret;
}


