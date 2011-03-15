#include <iostream>
#include <sstream>
#include "store.hpp"
#include "types.hpp"
#include "number.hpp"

word Store::get(unsigned int offset) const
{
	// TODO: Bounds checking
	// TODO: Disable if not allocated?
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
	allocated[offset] = true;
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
	allocated[offset/4] = true;
}

word& Store::operator[](unsigned int offset) 
{
	// TODO: Bounds checking
	return words[offset];	
}

void Store::clear(unsigned int offset, unsigned int length)
{
	unsigned int m = 0;

	// TODO: Bounds checking
	m = offset + length;
	for(unsigned int i = offset; i < m; i++) {
		words[i] = 0; // XXX: Not really necessary...
		allocated[i] = false;
	}
}

unsigned int Store::numAllocated() const
{
	unsigned int n = 0;
	for(unsigned int i = 0; i < allocated.size(); i++) {
		if(allocated[i]) {
			n++;
		}
	}
	return n;
}

void Store::reset()
{
	// Reset memory.
	//words = vector<word>(words.size(), 0);
	//allocated = vector<bool>(allocated.size(), false);

	for(unsigned int i = 0; i < words.size(); i++) {
		words[i] = 0;
		allocated[i] = false;
	}
}

string Store::toString() const
{
	stringstream out;
	unsigned int j = 0;

	// TODO: Report allocation state
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

