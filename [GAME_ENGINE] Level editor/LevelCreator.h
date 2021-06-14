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

class LevelCreator
{
public:
	LevelCreator();

	void events_multiwindow();

	void reset_states();

	void events();
	void events_indp();
	void render();
private:
	void load_Level();
	void new_Level();
	void save_level();

	void reset_mapStates(); // zresetuj tak�e przyciski, kt�re wymagane s� do mapy

	void leftBar_module_events(); // zamiast osobnej klasy, bedzie do tego specjalna funkcja -> nie ma sensu tworzy� klasy

	void switch_Main_state();
	void switch_Management_state();
private:
	ScrollBar scrollBar_folders, map_optionsBar, objectType_optionsBar;

	Map map_edit_area;

	Bar_modules_left bar_modules_left; // przyciski po lewej stronie

	Text Level_name, Map_name;

	CoordinateBar_mouse mouse_cord;

	class Queue_events // g��wna klasa zarz�dzaj�ca kolejk� 
	{
		// 1. Limit w kolejce to 10000 element�w
		// 2. Je�li b�d� wyst�powa�y jakie� problemy to po prostu trzeba zminiejszy� limit
		// 3. Kolejka zdarze� b�dzie dotyczy�a wszystkich danych, nie tylko obiewkt�w na mapie
		// ale te� np. obszarowego usuwania, usuwania itd. czyli wszystkich zmian na mapie
	public:

	private:
		std::deque<int> koleja_main;
		std::deque<int> koleja_tmp;
	};

	Button plus, minus;

	//Event_handler event_handler{};
};