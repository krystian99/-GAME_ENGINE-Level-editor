#pragma once
#include <chrono>

class Timer
{
public:
	Timer(int mili_seconds); // ile czasu ma trwa�

	bool passed();

	void setStart(); // ustal punkt startowy
private:
	std::chrono::time_point<std::chrono::system_clock> start;

	int time;
};