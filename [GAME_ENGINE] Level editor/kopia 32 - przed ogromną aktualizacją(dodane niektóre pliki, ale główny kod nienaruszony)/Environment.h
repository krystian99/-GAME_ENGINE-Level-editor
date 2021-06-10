#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include <SDL_events.h>
#include "Menu_manager.h"

class Environment // g³ówna klasa steruj¹ca/operuj¹ca
{
public:
	Environment() :
		escape_pressed{ false },
		test{ false }
	{}

	void run();

	~Environment() {}
private:
	void events();
	void events_indp();
	void events_dpnd();
	void render();
private:
	SDL_Event event_handler;

	MENU menu;

	//TEST
	//static unsigned long long ev_counter;
	//static unsigned long long ev_idnp_counter;
	//END TEST
	bool escape_pressed, test;

	LevelCreator level_editor;
};