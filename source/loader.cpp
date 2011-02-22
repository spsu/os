#include <cstdio>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp> // gcc does not support TR1 <regex> yet
#include <vector>

#include "loader.hpp"
#include "memory.hpp"

using namespace std;
//using namespace boost;


void Loader::loadDisk(Memory* memory)
{
	enum read_state { 
		NONE, 
		JOB_HEADER, 
		JOB_CONTENTS, 
		DATA_HEADER, 
		DATA_CONTENTS
	};

	static const boost::regex regex_job_header("JOB (\\w+) (\\w+) (\\w+)", 
		boost::regbase::normal | boost::regbase::icase);
	static const boost::regex regex_data_header("DATA (\\w+) (\\w+) (\\w+)", 
		boost::regbase::normal | boost::regbase::icase);
	static const boost::regex regex_memory_contents("(0x\\w+)", 
		boost::regbase::normal | boost::regbase::icase);

	ifstream file; 
	read_state state(NONE);
	read_state nextState(NONE);
	unsigned int memPos = 0;

	file.open(filename, ios::in);

	while(file.good()) 
	{
		string line;
		boost::smatch result;

		getline(file, line);

		if(boost::regex_search(line, result, regex_job_header))
		{
			state = JOB_HEADER;
			nextState = JOB_CONTENTS;

			// TODO: Save this data to PCB

			/*cout << "JOB: ";
			cout << result[1];
			cout << result[2];
			cout << result[3];
			cout << endl;
			cout << endl;*/
		}
		else if(boost::regex_search(line, result, regex_data_header))
		{
			state = DATA_HEADER;
			nextState = DATA_CONTENTS;

			// TODO: Save this data to PCB
			
			/*cout << "DATA: ";
			cout << result[1];
			cout << result[2];
			cout << result[3];
			cout << endl;
			cout << endl;*/
		}
		else if(boost::regex_search(line, result, regex_memory_contents))
		{
			state = nextState;		
			nextState = NONE; 

			int val = 10;

			cout << "DATA: ";
			cout << result[1];
			cout << ",  ";

			memory->set(memPos, val);
			memPos++;
		}



	}

	// XXX / TODO: Close the file!

}
