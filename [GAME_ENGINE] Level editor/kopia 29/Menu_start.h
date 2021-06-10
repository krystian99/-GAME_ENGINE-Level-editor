#pragma once
#include "Menu_base.h"
#include <string>
#include "Button_Menu.h"
#include "InputArea.h"
#include <memory>
#include <vector>
class Menu_start : public Menu_base
{
public:
	Menu_start();

	void events();
	void events_indp();
	void render();

	~Menu_start() {}
private:
	std::unique_ptr<Button_Menu> New, Load;

	std::unique_ptr<InputArea> input_levelname, input_background;
};