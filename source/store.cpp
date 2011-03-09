#include <iostream>
#include <sstream>
#include "store.hpp"
#include "types.hpp"
#include "number.hpp"

word Store::get(unsigned int offset) const
{
	// TODO: Bounds checking
	return words[offset];
}

unsigned int Store::getByte(unsigned int offset) const
{
	string bin = "";

	bin = dec_to_bin(words[offset/4]);
	bin = bin.substr((offset % 4) * 8, 8);

	return bin_to_dec(bin);
}

void Store::set(unsigned int offset, word data)
{
	// TODO: Bounds checking
	words[offset] = data;
}

void Store::setByte(unsigned int offset, int data)
{
	string bin = "";
	string repl = "";

	// No zerofill (or padding) -- add it here. 
	repl = dec_to_bin(data, false, false);
	while(repl.size() < 8) {
		repl.insert(0, "0");
	}

	bin = dec_to_bin(words[offset/4]);
	bin = bin.replace((offset % 4) * 8, 8, repl); 

	words[offset/4] = bin_to_dec(bin);
}

word& Store::operator[](unsigned int offset) 
{
	// TODO: Bounds checking
	return words[offset];	
}

void Store::reset()
{
	words = vector<word>(words.size(), 0); // Reset memory.
}

string Store::toString() const
{
	stringstream out;
	unsigned int j = 0;

	for(unsigned int i = 0; i < words.size(); i++) {
		out << i << ": " << words[i] << "\t";
		// XXX: This formatting is NOT correct!
		if(words[i] <= 9) {
			out << "\t\t";
		}
		else if(words[i] < 1000000000) {
			out << "\t";
		}

		j++;
		if(j % 5 == 0) {
			out << endl;
			j = 0;
		}
	}
	out << endl;
	return out.str();
}
