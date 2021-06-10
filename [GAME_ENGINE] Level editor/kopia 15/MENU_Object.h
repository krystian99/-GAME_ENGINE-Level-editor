#pragma once
#include <vector>
#include "Button_Menu.h"
#include <SDL_rect.h>
#include "APP_State.h"
#include "Menu_State.h"
#include <string>

class MENU_Object
{
	struct OBJ_info {
		SDL_Rect rt; // po³ozenie przycisku
		MENU_STATE next_menuState; // kolejne menu
		APP_state next_appState;
		std::string renderTEXT;
	};
public:
	MENU_Object() {}

	void setButtons(APP_state & app, MENU_STATE & state, const std::vector<OBJ_info> & bts);

	void load_images(std::string str);

	void events(SDL_Renderer * rn);

	~MENU_Object();
private:
	std::vector<Button_Menu> buttons;
};

