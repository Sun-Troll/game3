#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
	:
	current(steady_clock::now())
{
}

float FrameTimer::TimePassed()
{
	const auto last = current;
	current = steady_clock::now();
	const duration<float> dur = current - last;
	return dur.count();
}
