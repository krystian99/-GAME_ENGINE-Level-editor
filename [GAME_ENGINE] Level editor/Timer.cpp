#include "Timer.h"

Timer::Timer(int miliseconds)
{
	time = miliseconds;
}

void Timer::setStart()
{
	start = std::chrono::system_clock::now();
}

bool Timer::passed() // czy min�� okre�lony czas? Je�li tak to zwr�� true
{
	auto passed_time = std::chrono::duration<double, std::milli>(std::chrono::system_clock::now() - start);

	if (passed_time.count() >= time)
		return true;
	return false;
}