#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include "Menu_creator.h"
#include "APP_State.h"
#include <thread>

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
	~Environment();
private:
	void events();

	void render();

	void Init();

	void start_render();

	void switch_AppState_Events();
	void switch_AppState_Render();
private:
	double scaleW, scaleH;

	APP_state state;

	SDL_Event ev;

	bool running;

	MENU menu;
	LevelCreator Level_Environment;
};

