#include "utility.h"

class Timer
{
public:
	Timer();
	//constructor - turns on the timer

	double elapsed_time();
	//compute elapsed time between start and stop

	void reset();
	//restarts the timer

private:
	clock_t start_time;
	//type of value returned by system function clock()
};
/*****************END TIMER CLASS DEFINITION********/








/**************Implementation Timer class functions************/
Timer::Timer()
//constructor - turns on the timer
{
	start_time = clock();
}

double Timer::elapsed_time()
//compute elapsed time between start and stop
{
	clock_t end_time = clock();

	return ((double)(end_time - start_time)) / ((double)CLK_TCK);
}

void Timer::reset()
//restarts the timer
{
	start_time = clock();
}
