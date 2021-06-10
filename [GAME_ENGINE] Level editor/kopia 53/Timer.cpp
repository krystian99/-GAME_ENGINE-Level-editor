#include "Timer.h"

Timer::Timer(int miliseconds)
{
	time = miliseconds;
}

void Timer::setStart()
{
	start = std::chrono::system_clock::now();
}

bool Timer::passed() // czy min¹³ okreœlony czas? Jeœli tak to zwróæ true
{
	auto passed_time = std::chrono::duration<double, std::milli>(std::chrono::system_clock::now() - start);

	if (passed_time.count() >= time)
		return true;
	return false;
}