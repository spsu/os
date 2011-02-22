#include <iostream>
#include "memory.hpp"
#include "types.hpp"

word Memory::get(unsigned int offset) const
{
	// TODO: Bounds checking
	return words[offset];
}

void Memory::set(unsigned int offset, word data)
{
	// TODO: Bounds checking
	words[offset] = data;
}

void Memory::print() const
{
	for(unsigned int i = 0; i < words.size(); i++)
		cout << i << ": " << words[i] << ",  "; //<< endl;
}
