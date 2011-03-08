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
			// Extract job details
			curPcb = new Pcb();

			curPcb->jobStart = memPos;
			curPcb->priority = hex_to_dec(result[3]);
			curPcb->jobLength = hex_to_dec(result[2]);

			pcbList->push_back(curPcb);
		}
		else if(regex_search(line, result, regex_data_header))
		{
			// Extract data details
			int in = hex_to_dec(result[1]);
			int out = hex_to_dec(result[2]);
			int temp = hex_to_dec(result[3]);

			curPcb->dataStart = memPos;
			curPcb->dataInLength = in;
			curPcb->dataOutLength = out;
			curPcb->dataTempLength = temp;
			curPcb->dataLength = in + out + temp;
		}
		else if(regex_search(line, result, regex_memory_contents))
		{
			// Load job instructions or data to the memory space
			memory->set(memPos, hex_to_dec(result[1]));
			memPos++;
		}
	}

	// XXX / TODO: Close the file!
	
	return pcbList;
}

