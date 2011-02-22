#ifndef BT_OS_LOADER
#define BT_OS_LOADER

#include <string>

using namespace std;

class Memory;

class Loader 
{
	public:
		/**
		 * CTOR: Filename unspec'd.
		 */
		Loader()
			: filename("") {};

		/**
		 * CTOR: Set filename.
		 */
		Loader(string fname) 
			: filename(fname) {};

		// TODO: Return type, etc.
		void loadDisk(Memory* mem);

	private:
		// Name of file with instructions.
		string filename;
};

#endif
