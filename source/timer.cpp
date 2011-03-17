#include "timer.hpp"

void Timer::start()
{
	if(running) {
		return;
	}

	cpuTimeStart = clock();
	gettimeofday(&wallTimeStart, NULL);	
	
	running = true;
}

void Timer::end()
{
	clock_t endCpu;
	timeval endWall;
	double a, b;
	
	if(!running) {
		return;
	}

	endCpu = clock();
	gettimeofday(&endWall, NULL);	

	a = wallTimeStart.tv_sec + (wallTimeStart.tv_usec/1000000.0);
	b = endWall.tv_sec + (endWall.tv_usec/1000000.0);

	cpuTimeTotal += ((double)(cpuTimeStart + endCpu)) / CLOCKS_PER_SEC;
	wallTimeTotal += b - a;
	
	cpuTimeStart = 0.0;
	wallTimeStart.tv_sec = 0.0;
	wallTimeStart.tv_usec = 0.0;

	running = false;
}

void Timer::reset()
{
	cpuTimeStart = 0;
	cpuTimeTotal = 0.0;
	wallTimeStart.tv_sec = 0.0;
	wallTimeStart.tv_usec = 0.0;
	running = false;
}

double Timer::getCpuTime() const
{
	clock_t end;
	double curLen = 0.0;

	if(!running) {
		return cpuTimeTotal;
	}

	// Include current runtime
	end = clock();
	curLen = ((double)(cpuTimeStart + end)) / CLOCKS_PER_SEC;
	return cpuTimeTotal + curLen;
}

double Timer::getWallTime() const
{
	timeval end;
	double a, b;
	
	if(!running) {
		return wallTimeTotal;
	}

	// Include current runtime

	gettimeofday(&end, NULL);	

	a = wallTimeStart.tv_sec + (wallTimeStart.tv_usec/1000000.0);
	b = end.tv_sec + (end.tv_usec/1000000.0);

	return wallTimeTotal + (b - a);
}

