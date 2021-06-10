#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include <SDL_events.h>
#include "Menu_manager.h"

class Environment // g³ówna klasa steruj¹ca/operuj¹ca
{
public:
	void run();
private:
	void events();
	void events_indp();
	void events_dpnd();
	void render();
private:
	SDL_Event event_handler;

	MENU menu;

	bool escape_pressed{ false }, test{ false };

	LevelCreator level_editor;
};