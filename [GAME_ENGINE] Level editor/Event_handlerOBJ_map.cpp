#include "Event_handlerOBJ_map.h"

Event_handlerOBJ_map::Event_handlerOBJ_map(Map* map, Map_state map_event)
{
	this->map = map;
	this->map_event = map_event;
}

void Event_handlerOBJ_map::render()
{
	map->render();
}
