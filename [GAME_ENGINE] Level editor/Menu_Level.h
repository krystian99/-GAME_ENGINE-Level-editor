#pragma once
#include <string>
#include "InputArea.h"
#include "Folder_button.h"
#include "Image.h"
#include "Button.h"
#include "Module_base.h"

class Menu_Level : public Module_base
{
public:
	Menu_Level();

	void events();
	void events_indp();
	void render();

	~Menu_Level() {}
private:
	Button New, Load;

	Image currentMenu;

	Image map_nameInput_button, level_nameInput_button;

	Folder_button input_levelName, input_mapName;

	InputArea input_area_level, input_area_map;
};