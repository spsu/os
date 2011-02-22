#include <iostream>
#include "memory.hpp"
#include "types.hpp"

word Memory::get(int offset)
{
	// TODO: Bounds checking
	return words[offset];
}

void Memory::set(int offset, word data)
{
	// TODO: Bounds checking
	words[offset] = data;
}

void Memory::print()
{
	for(unsigned int i = 0; i < words.size(); i++)
		cout << i << ": " << words[i] << endl;
}
