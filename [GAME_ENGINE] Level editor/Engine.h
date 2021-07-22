#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include <SDL_events.h>
#include "Menu_manager.h"
#include "Animation_management.h"
#include "Script_Editor.h"
#include "Module_Object.h"

// g³ówna klasa steruj¹ca/operuj¹ca
class Engine : public Module_Object
{
public:
	Engine();

	void run();
private:
	void events();

	void events_indp();
	void events_dpnd();

	void render();
private:
	void on_keyboardKey_ESCAPE_1hit() override;
	void on_keyboardKey_X_1hit() override;
private:
	SDL_Event event_handler{};

	MENU menu;

	LevelCreator level_editor;

	Animation_management animation_config_creator;

	Script_Editor script_editor;
};
