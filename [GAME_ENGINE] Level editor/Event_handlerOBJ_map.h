#pragma once
#include "Map_states.h"
#include "Map.h"
#include "Event_handlerOBJ.h"
#include "Map_events.h"


class Event_handlerOBJ_map : public Event_handlerOBJ
{
	using Func = void (*)(Map*);
public:
	Event_handlerOBJ_map(Map* map, Func);// , Map_state map_event = Map_state::NONE);
	~Event_handlerOBJ_map();
private:
	void process();
	//void mouse_events() {}
private:
	Map* map;
	Func func;
	//Map_state map_event;
};

