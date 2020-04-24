#include "Timer.h"



Timer::Timer()
{

	last = std::chrono::steady_clock::now();
}

float Timer::Mark()
{
	auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

