#pragma once
#include "Event_handlerOBJ.h"
#include <queue>
#include <SDL_events.h>

using namespace std;

class Event_handler
{
public:
	static void pop();

	static bool empty() { return events.empty(); }

	static void push(Event_handlerOBJ* eventOBJ);

private:
	static queue<Event_handlerOBJ*> events;
};