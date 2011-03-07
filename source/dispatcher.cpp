#include "dispatcher.hpp"
#include "cpu.hpp"
#include "pcb.hpp"

// TODO
void Dispatcher::dispatch(Pcb* pcb)
{
	cpu->registers.empty();
	cpu->cache.empty();
	cpu->pc = 0;
}
