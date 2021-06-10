#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include <SDL_events.h>
#include "Menu_manager.h"
#include "Animation_management.h"

class Environment // g��wna klasa steruj�ca/operuj�ca
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

	LevelCreator level_editor;

	Animation_management animation_config_creator;

	bool escape_pressed{ false }, test{ false };
};