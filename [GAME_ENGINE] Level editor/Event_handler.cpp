#include "Event_handler.h"

queue<Event_handlerOBJ*> Event_handler::events{};

void Event_handler::process()
{
	//events.front()->run();

	delete events.front();

	events.pop();
}

void Event_handler::push(Event_handlerOBJ* eventOBJ)
{
	events.push(eventOBJ);
}
