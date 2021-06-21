#pragma once
#include <fstream>
#include "CoordinateBar_mouse.h"
#include "Map.h"
#include "ScrollBar.h"
#include "Menu_local.h"
#include "Text.h"
#include "Button_input.h"
#include "Bar_modules_left.h"
#include <queue>
#include "Module_base.h"

class LevelCreator : public Module_base
{
public:
	LevelCreator();

	bool isUpdated() const { return map_edit_area.isUpdated(); }

	void events_multiwindow();

	void reset_states();

	void events();
	void events_indp();
	void render();
private:
	void load_Level();
	void new_Level();
	void save_level();

	void reset_mapStates(); // zresetuj tak¿e przyciski, które wymagane s¹ do mapy

	void leftBar_module_events(); // zamiast osobnej klasy, bedzie do tego specjalna funkcja -> nie ma sensu tworzyæ klasy

	void keyboardHandler();

	void switch_Main_state();
	void switch_Management_state();
private:
	ScrollBar<ScrollBar_orient::VERTICAL> scrollBar_folders, objectType_optionsBar;
	ScrollBar<ScrollBar_orient::HORIZONTAL> map_optionsBar;

	Map map_edit_area;

	Bar_modules_left bar_modules_left; // przyciski po lewej stronie

	Text Level_name, Map_name;

	CoordinateBar_mouse mouse_cord;

	Button plus, minus;
};