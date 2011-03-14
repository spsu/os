//#include <iostream>
#include "memory.hpp"
//#include "types.hpp"
#include <iostream>

using namespace std;

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

int Memory::findLargestContiguousHole(unsigned int reqSize) const
{
	int largestPos = -1;
	int largestSize = 0;
	int curPos = -1;
	int curSize = 0;

	for(unsigned int i = 0; i < allocated.size(); i++)
	{
		if(allocated[i]) {
			curSize = 0;
			curPos = -1;
			continue;
		}

		// Set start site of hole
		if(curPos < 0) {
			curPos = i;
		}
		curSize++;
		
		if(curSize > largestSize) {
			largestSize = curSize;
			largestPos = curPos;
		}
	}

	if(largestSize < reqSize) {
		return -1;
	}
	return largestPos;
}

int Memory::findSmallestContiguousHole(unsigned int reqSize) const
{
	int goodPos = -1;
	int goodSize = -1;
	int curPos = -1;
	int curSize = 0;

	for(unsigned int i = 0; i < allocated.size(); i++)
	{
		if(allocated[i]) {
			// Retain the smallest hole that fits our size requirements.
			if(curSize >= reqSize && (curSize < goodSize || goodSize == -1)) {
				goodSize = curSize;
				goodPos = curPos;
			}
			curSize = 0;
			curPos = -1;
			continue;
		}

		// Set start site of hole
		if(curPos < 0) {
			curPos = i;
		}
		curSize++;
	}

	// In the event only one hole exists: 
	if(goodSize == -1 && curSize > 0) {
		goodSize = curSize;
		goodPos = curPos;
	}

	if(goodSize < reqSize) {
		return -1;
	}
	return goodPos;
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

