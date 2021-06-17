#pragma once
#include "ScrollBar.h"
#include "Menu_local.h"

class Bar_modules_left // klasa steruj¹ca modu³ami i skryptami zwi¹zanymi z pocyzcj¹ tych obiektów
{
	friend class LevelCreator;
public:
	Bar_modules_left();

	void reset_states();

	void events();
	void events_multiwindow();
	void events_indp();
	void render();
private:
	Menu_local menu_options;
	ScrollBar<ScrollBar_orient::VERTICAL> modules_list;

	bool moving_objects{ false };
};