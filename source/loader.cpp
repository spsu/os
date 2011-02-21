#include "loader.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
//#include <regex> // Using Boost TR1 equiv.
#include <boost/regex.hpp>
#include <vector>

using namespace std;

void Loader::loadDisk()
{
	ifstream f; 

	f.open(filename, ios::in);
	while(f.good()) 
	{
		string line;

		boost::regex regex_job("JOB (\\w+) (\\w+) (\\w+)", 
				boost::regbase::normal | boost::regbase::icase);
		boost::regex regex_data("DATA (\\w+) (\\w+) (\\w+)", 
				boost::regbase::normal | boost::regbase::icase);

		boost::smatch result;

		getline(f, line);

		// TODO: Implement a state machine here to extract data

		if(boost::regex_search(line, result, regex_job)) {
			cout << "JOB: ";
			cout << result[1];
			cout << result[2];
			cout << result[3];
			cout << endl;
			cout << endl;
		}
		else if(boost::regex_search(line, result, regex_data)) {
			cout << "DATA: ";
			cout << result[1];
			cout << result[2];
			cout << result[3];
			cout << endl;
			cout << endl;
		}

	}

}
