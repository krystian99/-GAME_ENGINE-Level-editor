#include "Event_handler.h"

queue<Function> Event_handler::events{};
SDL_Event Event_handler::event_handler;

void Event_handler::push(Function p)
{
	events.push(p);
}

void Event_handler::process()
{
	events.front().run();
}

Function::Function(FUNCTION_VOID_NO_ARG f)
{
	function = f;
}

void Function::run()
{
	function();
}