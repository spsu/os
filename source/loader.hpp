#ifndef OS_LOADER
#define OS_LOADER

#include <string>

using namespace std;

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
		void loadDisk();

	private:
		// Name of file with instructions.
		string filename;
};

#endif
