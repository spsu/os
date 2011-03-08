#include <iostream>
#include <sstream>
#include "store.hpp"
#include "types.hpp"

word Store::get(unsigned int offset) const
{
	// TODO: Bounds checking
	return words[offset];
}

void Store::set(unsigned int offset, word data)
{
	// TODO: Bounds checking
	words[offset] = data;
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
