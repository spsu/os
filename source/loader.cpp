#include "loader.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;
//using namespace std::tr1;

Loader::Loader(string fname)
{
	ifstream f; 

	f.open(fname, ios::in);
	while(f.good()) {
		string line;

		getline(f, line);

		cout << line << endl;
	}

}
