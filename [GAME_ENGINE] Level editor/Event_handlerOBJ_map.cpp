#include "Event_handlerOBJ_map.h"

Event_handlerOBJ_map::Event_handlerOBJ_map(Map* map, Func func)// Map_state map_event = Map_state::NONE)
{
	this->map = map;
	this->func = func;
}

Event_handlerOBJ_map::~Event_handlerOBJ_map()
{
	process();
}

void Event_handlerOBJ_map::process()
{
	func(map);
}
