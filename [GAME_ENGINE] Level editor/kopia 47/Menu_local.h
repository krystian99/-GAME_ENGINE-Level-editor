#pragma once
#include <vector>
#include "Button.h"
#include <SDL_render.h>
#include "Texture.h"
#include <string>

class Menu_local // to te¿ jest przycisk i powinien dziedziczyæ po klasie Button
{
public:
	Menu_local(SDL_Rect rt, const std::string & tx_str, bool Active, bool can_hide, int expand);

	void render();
	void events();

	void operator=(const std::vector<Button*> & Buttons);
private:
	void mouse_handler();

	void script_run();
	void script_leave();
private:
	std::vector<Button*> buttons;

	bool script_finished{ true };

	Texture tX;

	bool active, can_hide;

	int button_height;

	Button * current_button{ nullptr };

	SDL_Rect position;
};