#pragma once
#include <fstream>
#include "Coordinates_bar.h"
#include "Menu_localEditor.h"
#include "Map_EditArea.h"
#include "ScrollBar.h"

class LevelCreator
{
public:
	LevelCreator();

	void events();
	void events_indp();
	void render();
private:
	void load_Level();
	void new_Level();

	void switch_Main_state();
	void switch_Management_state();

	void save_level();
private:
	std::ifstream level_load; // �aduje dane ca�ego levela
	std::ofstream level_save; // zapisuje dane ca�ego levela

	ScrollBar scrollBar_folders, map_optionsBar;

	Map_EditArea map_edit_area;

	Menu_localEditor localMenu_bar; // lokalne menu - przyciski LEVEL, OBJECTS itd. zawieraj� 

	Coordinates_bar map_coordinate, mouse_cord;
};