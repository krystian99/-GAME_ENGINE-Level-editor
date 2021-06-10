#pragma once
//#include "ScrollBar.h"
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

	//void renderAll();

	void switch_AppState();
	void switch_menuState();
	void switch_LevelCreatorState();
	void switch_MenuCreatorState();
private:
	APP_state state;
	//ScrollBar sbDynamic, sbKey, sbStatic; // sb - scroll bar
	//LevelCreator edit_Area;
	MENU menu;
};

