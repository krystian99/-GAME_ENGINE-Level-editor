#pragma once
#include "Map_states.h"
#include "Map.h"
#include "Event_handlerOBJ.h"

class Event_handlerOBJ_map : public Event_handlerOBJ
{
	Event_handlerOBJ_map(Map* map, Map_state map_event);

	void run() { render(); }
private:
	void render();
	//void mouse_events() {}
private:
	Map* map;
	Map_state map_event;
};

