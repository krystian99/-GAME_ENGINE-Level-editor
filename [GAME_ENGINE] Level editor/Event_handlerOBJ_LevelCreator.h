#pragma once
#include "Map_states.h"
#include "LevelCreator.h"
#include "Event_handlerOBJ.h"

class Event_handlerOBJ_LevelCreator
{
	using Func = void (*)(LevelCreator*);
public:
	Event_handlerOBJ_LevelCreator(LevelCreator* map, Func);// , Map_state map_event = Map_state::NONE);
	~Event_handlerOBJ_LevelCreator();
private:
	void process();
	//void mouse_events() {}
private:
	LevelCreator* map;
	Func func;
	//Map_state map_event;
};

