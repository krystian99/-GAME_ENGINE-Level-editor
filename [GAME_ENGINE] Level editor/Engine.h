#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include <SDL_events.h>
#include "Menu_manager.h"
#include "Animation_management.h"
#include "Script_Editor.h"

class Engine // g??wna klasa steruj?ca/operuj?ca
{
public:
	void run();
private:
	void events();
	void events_indp();
	void events_dpnd();
	void render();
private:
	void render_events();
private:
	SDL_Event event_handler;

	MENU menu;

	LevelCreator level_editor;

	Animation_management animation_config_creator;

	Script_Editor script_editor;

	bool escape_pressed{ false }, test{ false };
};