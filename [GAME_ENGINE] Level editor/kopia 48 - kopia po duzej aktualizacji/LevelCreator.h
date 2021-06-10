#pragma once
#include <fstream>
#include "Coordinates_bar.h"
#include "Map.h"
#include "ScrollBar.h"
#include "Menu_local.h"
#include "Text.h"
#include "Button_input.h"

class LevelCreator
{
public:
	LevelCreator();

	void events_multiwindow();

	void events();
	void events_indp();
	void render();
private:
	void load_Level();
	void new_Level();
	void save_level();

	void switch_Main_state();
	void switch_Management_state();
private:
	std::ifstream level_load; // ³aduje dane ca³ego levela
	std::ofstream level_save; // zapisuje dane ca³ego levela

	ScrollBar scrollBar_folders, map_optionsBar, objectType_optionsBar, objects_typePanel;

	Map map_edit_area;

	Menu_local menu_options;

	Text Level_name, Map_name;

	Coordinates_bar map_coordinate, mouse_cord;

	Button plus, minus;
};