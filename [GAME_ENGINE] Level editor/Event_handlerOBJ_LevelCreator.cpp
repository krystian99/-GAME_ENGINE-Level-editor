#include "Event_handlerOBJ_LevelCreator.h"

Event_handlerOBJ_LevelCreator::Event_handlerOBJ_LevelCreator(LevelCreator* map, Func func)// Map_state map_event = Map_state::NONE)
{
	this->map = map;
	this->func = func;
}

Event_handlerOBJ_LevelCreator::~Event_handlerOBJ_LevelCreator()
{
	process();
}

void Event_handlerOBJ_LevelCreator::process()
{
	func(map);
}