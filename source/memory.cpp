#include "memory.hpp"
#include "number.hpp"
#include <iostream>
#include <fstream>

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

	if(largestSize < (int)reqSize) {
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
			if(curSize >= (int)reqSize && (curSize < goodSize || goodSize == -1)) {
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

	if(goodSize < (int)reqSize) {
		return -1;
	}
	return goodPos;
}

void Memory::writeDisk(string fname)
{
	ofstream ofile;
	ofile.open(fname, ifstream::out);

	for(unsigned int i = 0; i < words.size(); i++)
	{
		ofile << i << ":  \t";
		ofile << dec_to_bin(words[i]) << endl;
	}
	ofile.close();
}

