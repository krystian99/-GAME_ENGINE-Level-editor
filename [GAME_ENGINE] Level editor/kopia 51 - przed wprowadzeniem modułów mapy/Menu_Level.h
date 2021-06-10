#pragma once
#include "Menu_base.h"
#include <string>
#include "Button_Menu.h"
#include "InputArea.h"

class Menu_Level : public Menu_base
{
public:
	Menu_Level();

	void events();
	void events_indp();
	void render();

	~Menu_Level() {}
private:
	Button_Menu New, Load;

	InputArea input_levelname, input_background;
};