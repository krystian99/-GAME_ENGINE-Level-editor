#include "Event_handler.h"

void Event_handler::push(FUNCTION f)
{
	events.push(f);
}
