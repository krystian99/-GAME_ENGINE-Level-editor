#pragma once
#include "Renderer.h"

class Map;

namespace Map_events
{
	void events_enemies(Map*);
	void render_enemies(Map* map);

	void render_map(Map* map);
}