#include <iostream>
#include "loader.hpp"
#include "memory.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	Loader *a = 0;
	Memory *m = 0;

	a = new Loader("data/datafile1.txt");
	a->loadDisk();

	m = new Memory(2048);
	cout << m->size() << endl;

	// XXX: Memory test
	m->set(2030, 0xfff);
	m->set(2031, 9000);
	m->print();

	return 0;
}
