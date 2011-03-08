#include "dispatcher.hpp"
#include "cpu.hpp"
#include "pcb.hpp"

// TODO
void Dispatcher::dispatch(Pcb* pcb)
{
	cpu->registers.reset();
	cpu->cache.reset();
	cpu->pc = 0;
}
