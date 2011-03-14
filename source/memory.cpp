//#include <iostream>
#include "memory.hpp"
//#include "types.hpp"

Memory::Memory() :
	Store()
{
	pthread_mutex_init(&mux, NULL);
}

Memory::Memory(int numWords):
	Store(numWords)
{
	pthread_mutex_init(&mux, NULL);
}

void Memory::acquire()
{
	pthread_mutex_lock(&mux);
}

void Memory::release()
{
	pthread_mutex_unlock(&mux);
}

/*word Memory::get(unsigned int offset) const
{
	// TODO: Bounds checking
	// TODO: Mutex
}*/

/*void Memory::set(unsigned int offset, word data)
{
	// TODO: Bounds checking
	// TODO: Mutex
}*/

