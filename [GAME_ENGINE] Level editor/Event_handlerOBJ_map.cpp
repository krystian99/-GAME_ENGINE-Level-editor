#include "Event_handlerOBJ_map.h"
//#include "Renderer.h"

Event_handlerOBJ_map::Event_handlerOBJ_map(Map* map)// Map_state map_event = Map_state::NONE)
{
	this->map = map;
	//this->map_event = map_event;
}

Event_handlerOBJ_map::~Event_handlerOBJ_map()
{
	run();
}

void Event_handlerOBJ_map::render()
{
	map->render();
}
