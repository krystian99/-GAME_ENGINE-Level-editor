#pragma once
#include "Module_base.h"
#include "Enemy.h"
#include <SDL_rect.h>

enum SingleOBJmove_events
{
	SELECTING,
	MOVING_OBJ,
	SET_OBJ
};

class singleOBJmove_structure : public Module_base
{
public:
	void set(Enemy* enemy);

	void reset()
	{
		current_enemy = nullptr;
	}
	
	void events(bool mouse_over, SDL_Rect edit_area);

	void events();
	void render();

	Enemy* current_enemy;

	int px_left;
	int px_up;

private:
	SingleOBJmove_events state;
};