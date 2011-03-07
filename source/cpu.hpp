#ifndef BT_OS_CPU
#define BT_OS_CPU

#include "store.hpp"

class Cpu 
{
	friend class Dispatcher;

	public:
		/**
		 * CTOR.
		 */
		Cpu();

		/**
		 * Execute loop.
		 * TODO
		 */
		void execute();

	private:
		/**
		 * Registers (16 total).
		 * 	 All registers are general purpose, except:
		 * 	  - 1st is accumulator
		 * 	  - 2nd is zero register
		 */
		Store registers;

		/**
		 * Cache
		 *   Stores the program text section locally.
		 *   TODO: Figure out a good size for this. 
		 *   	   Size of largest program is good. 
		 */
		Store cache;

		/**
		 * Program counter.
		 *   TODO: Documentation.
		 */
		word pc;
};

#endif
