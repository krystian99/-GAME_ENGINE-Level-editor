#pragma once
//#include "ScrollBar.h"
#include "LevelCreator.h"
#include "MENU.h"
#include "Menu_creator.h"
#include "APP_State.h"

/// ========================================================================================
// Prefixy i Suffixy odpowiednich obiekt�w:
// - LC - Level Creator
// - MC - Menu Creator
// - E - Environment( g��wna klasa )
// - M - Menu
/// ========================================================================================

// powiedzmy v50(testy renderowania i aplikacji zako�czone): 
// przebudowa ca�ego engine'a w tym:
// - dodanie menus�w
// - przebudowa klasy button - od teraz button jest abstrakcyjn� klas� bazow�
// - i wiele innych

class Environment // g��wna klasa steruj�ca/operuj�ca
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

