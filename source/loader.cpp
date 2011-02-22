#include <cstdio>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp> // gcc does not support TR1 <regex> yet
#include <vector>

#include "loader.hpp"
#include "memory.hpp"
#include "number.hpp"
#include "pcb.hpp"

using namespace std;
using namespace boost;

PcbList* Loader::loadDisk(Memory* memory)
{
	static const regex regex_job_header("JOB (\\w+) (\\w+) (\\w+)", 
		regbase::normal | regbase::icase);
	static const regex regex_data_header("DATA (\\w+) (\\w+) (\\w+)", 
		regbase::normal | regbase::icase);
	static const regex regex_memory_contents("(0x\\w+)", 
		regbase::normal | regbase::icase);

	ifstream file; 
	PcbList* pcbList = new vector<Pcb*>();
	Pcb* curPcb = 0;
	unsigned int memPos = 0;

	file.open(filename, ios::in);

	while(file.good()) 
	{
		string line;
		smatch result;

		getline(file, line);

		if(regex_search(line, result, regex_job_header))
		{
			curPcb = new Pcb();
			pcbList->push_back(curPcb);

			curPcb->diskInstructionsStart = memPos;

			curPcb->priority = hex_to_dec(result[3]);
			curPcb->diskInstructionsLimit = hex_to_dec(result[2]);
		}
		else if(regex_search(line, result, regex_data_header))
		{
			curPcb->diskDataStart = memPos;
			// TODO: Input, Output, and Temp??
		}
		else if(regex_search(line, result, regex_memory_contents))
		{
			// Load data to the memory space
			memory->set(memPos, hex_to_dec(result[1]));
			memPos++;
		}
	}

	// XXX / TODO: Close the file!
	
	return pcbList;
}

