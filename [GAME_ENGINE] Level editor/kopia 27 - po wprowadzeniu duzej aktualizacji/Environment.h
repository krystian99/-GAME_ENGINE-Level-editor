#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include "APP_State.h"
#include <SDL_events.h>

/// ========================================================================================
// Prefixy i Suffixy odpowiednich obiekt�w:
// - LC - Level Creator
// - MC - Menu Creator
// - E - Environment( g��wna klasa )
// - M - Menu
/// ========================================================================================

class Environment // g��wna klasa steruj�ca/operuj�ca
{
public:
	Environment();

	void run();

	~Environment() {}
private:
	void events();
	void render();
private:
	APP_state state;

	SDL_Event event_handler;

	bool running;

	MENU menu;
	LevelCreator Level_Environment;
};

