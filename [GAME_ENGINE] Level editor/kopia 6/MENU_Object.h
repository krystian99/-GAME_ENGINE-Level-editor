#pragma once
#include <vector>
#include "Button_Menu.h"
#include <SDL_rect.h>
#include <SDL_ttf.h>
#include "APP_State.h"
#include "Menu_State.h"

class MENU_Object
{
	struct OBJ_info {
		SDL_Rect rt; // po³ozenie przycisku
		MENU_STATE next_menuState; // kolejne menu
		APP_state next_appState;
	};
public:
	MENU_Object();

	void setButtons(const std::vector<OBJ_info> & bts);

	void events(APP_state & app_state, MENU_STATE & menu_state);

	~MENU_Object();
private:
	void render(SDL_Renderer * rn);
private:
	std::vector<Button_Menu> buttons;
};

