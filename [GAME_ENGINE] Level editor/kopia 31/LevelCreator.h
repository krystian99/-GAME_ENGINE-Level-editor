#pragma once
#include <vector>
#include <fstream>
#include "Button_Placing_EnemyOBJ.h"
#include "Coordinates_bar.h"
#include "Menu_localEditor.h"
#include "Map_EditArea.h"

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
	std::ifstream level_load; // ³aduje dane ca³ego levela
	std::ofstream level_save; // zapisuje dane ca³ego levela

	std::vector<Button*> buttons_mapOptions_bar;

	Map_EditArea map_edit_area;

	Button_Placing_EnemyOBJ button_enemyPlace_test;

	Menu_localEditor localMenu_bar; // lokalne menu - przyciski LEVEL, OBJECTS itd. zawieraj¹ 

	bool l_buttonPressing; // Czy klikniêty lewy przycisk przynajmniej raz? Je¿eli tak = true, w przeciwnym wypadku czekaj a¿ nie bêdzie naciœniety i = false.

	Coordinates_bar map_coordinate;
	Coordinates_bar mouse_cord;
};