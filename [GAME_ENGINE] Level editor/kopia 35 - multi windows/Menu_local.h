#pragma once
#include <vector>
#include "Button.h"
#include <SDL_render.h>
#include "Texture.h"
#include <string>

class Menu_local
{
public:
	Menu_local(SDL_Rect rt, const std::string & tx_str, bool Active, int expand);

	void render();
	void events();

	void operator=(const std::vector<Button*> & Buttons);
private:
	std::vector<Button*> buttons;

	Texture tX;

	bool active;

	int button_height;

	SDL_Rect position;
};