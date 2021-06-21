#pragma once
#include "Event_handlerOBJ.h"
#include <queue>

class Event_handler
{
public:
	static void process();

	static bool empty() { return events.empty(); }

	static void push(Event_handlerOBJ* eventOBJ);

private:
	static std::queue<Event_handlerOBJ*> events;
};