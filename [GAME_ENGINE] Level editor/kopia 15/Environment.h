#pragma once
#include "LevelCreator.h"
#include "MENU.h"
#include "Menu_creator.h"
#include "APP_State.h"

/// ========================================================================================
// Prefixy i Suffixy odpowiednich obiektów:
// - LC - Level Creator
// - MC - Menu Creator
// - E - Environment( g³ówna klasa )
// - M - Menu
/// ========================================================================================

// powiedzmy v50(testy renderowania i aplikacji zakoñczone): 
// przebudowa ca³ego engine'a w tym:
// - dodanie menusów
// - przebudowa klasy button - od teraz button jest abstrakcyjn¹ klas¹ bazow¹
// - i wiele innych

class Environment // g³ówna klasa steruj¹ca/operuj¹ca
{
public:
	Environment();
	void run();
	~Environment();
private:
	void events();

	void Init();

	void start_render();

	void switch_AppState_Events();
	void switch_AppState_Render();
private:
	double scaleW, scaleH;

	APP_state state;

	SDL_Event ev;

	int test;

	bool running;

	MENU menu;
	LevelCreator Level_Environment;
};

