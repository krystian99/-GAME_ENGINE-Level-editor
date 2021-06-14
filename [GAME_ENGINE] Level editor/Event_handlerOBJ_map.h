#pragma once
#include "Map_states.h"
#include "Map.h"
#include "Event_handlerOBJ.h"

class Event_handlerOBJ_map : public Event_handlerOBJ
{
public:
	Event_handlerOBJ_map(Map* map);// , Map_state map_event = Map_state::NONE);
	~Event_handlerOBJ_map();
private:
	void run() { render(); }
	void render();
	//void mouse_events() {}
private:
	Map* map;
	//Map_state map_event;
};

