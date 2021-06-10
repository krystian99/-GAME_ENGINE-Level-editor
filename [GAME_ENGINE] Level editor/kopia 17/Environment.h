#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include "Menu_creator.h"
#include "APP_State.h"
#include <thread>

/// ========================================================================================
// Prefixy i Suffixy odpowiednich obiektów:
// - LC - Level Creator
// - MC - Menu Creator
// - E - Environment( g³ówna klasa )
// - M - Menu
/// ========================================================================================

class Environment // g³ówna klasa steruj¹ca/operuj¹ca
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

