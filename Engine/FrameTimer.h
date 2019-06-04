#pragma once

#include <chrono>

struct FrameTimer
{
public:
	FrameTimer();
	float TimePassed();
private:
	std::chrono::steady_clock::time_point current;
};