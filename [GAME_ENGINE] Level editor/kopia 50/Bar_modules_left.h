#pragma once
#include "ScrollBar.h"
#include "Menu_local.h"

class Bar_modules_left // klasa steruj�ca modu�ami i skryptami zwi�zanymi z pocyzcj� tych obiekt�w
{
public:
	Bar_modules_left();

	void events();
	void events_indp();
	void render();
private:
	Menu_local menu_options;
	ScrollBar modules_list;

	bool moving_objects{ false };
};