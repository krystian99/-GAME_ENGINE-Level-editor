#include "Event_handler.h"

std::queue<Event_handlerOBJ*> Event_handler::events{};

void Event_handler::process()
{
	delete events.front();

	events.pop();
}

void Event_handler::push(Event_handlerOBJ* eventOBJ)
{
	events.push(eventOBJ);
}
