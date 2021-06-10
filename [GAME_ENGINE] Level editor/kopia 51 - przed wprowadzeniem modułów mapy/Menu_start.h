#pragma once
#include "Menu_base.h"
#include <string>
#include "Button_Menu.h"

class Menu_start : public Menu_base
{
public:
	Menu_start();

	void events();
	void events_indp();
	void render();

	~Menu_start() {}
private:
	Button_Menu level_menu, anim_menu;
};