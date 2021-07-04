#pragma once
#include "Module_base.h"
#include "Enemy.h"
#include <SDL_rect.h>

enum class SingleOBJmove_events
{
	NONE,
	SELECTING,
	MOVING_OBJ,
	READY_TO_SET,
	SET_OBJ
};

class singleOBJmove_structure : public Module_base
{
	using Enemies = std::vector<Enemy_ptr>;
public:
	singleOBJmove_structure(Enemies& en, const Rect& edit_a, const Rect& mapBG_a) :
		edit_area{ edit_a }, enemies{ en }, mapBG_area{ mapBG_a }
	{}

	void set(Enemy* enemy);

	void reset()
	{
		current_enemy = nullptr;
	}
	
	static void setState(SingleOBJmove_events st);

	void events();
	void events_indp();

	void render();

	Enemy* current_enemy{};

	int px_left{};
	int px_up{};
private:
	void reset_states(){}

	void movingOBJ_events();
	void selectingObject_events();

	void setOBJ_onMap();

	void mouseR_event();
	void mouseL_event();

	void mouse_handler();
private:
	const Rect& edit_area;
	const Rect& mapBG_area;

	Enemies& enemies;

	static SingleOBJmove_events state;
};