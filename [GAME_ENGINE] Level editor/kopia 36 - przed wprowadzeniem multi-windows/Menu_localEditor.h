#pragma once
// Menu lokalne tylko dla klasy LevelCreator. 
#include "Button_menuLocal_Level.h"
#include <vector>

class Menu_localEditor
{
public:
	Menu_localEditor();

	void events();
	void events_indp();
	void render();

	// resetuje wszystkie podmenu(ang. sub-menus)
	void reset();

	~Menu_localEditor() {}
private:
	Button_menuLocal_Level menu_level;
};