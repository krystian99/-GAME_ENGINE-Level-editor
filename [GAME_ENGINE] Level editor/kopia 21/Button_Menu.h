#pragma once
#include "Button_TEXT.h"
#include "APP_State.h"
#include "Menu_State.h"
#include <string>
#include "Font.h"

class Button_Menu : public Button_TEXT
{
public:
	Button_Menu(APP_state & aMain, const APP_state & st2, APP_state & recent_app, MENU_STATE & mMain, const MENU_STATE & st1, MENU_STATE & recent_menu) :
		mainState_menu{ mMain }, nextMenu_state{ st1 },
		main_state{ aMain }, nextState{ st2 },
		recent_state{ recent_menu },
		recentApp_state{ recent_app }
	{}

	void events();
	void events_independent();
	void render(SDL_Renderer * rn);

	~Button_Menu() {}
private:
	void moveText(const int & size);

	virtual void onClick();
	virtual void onMouseOver();

	void set_nextState_APP();

	void TEXT_render(SDL_Renderer * rn);
private:
	static const int FRAME_SIZE = 10;
	static const int MoveSize = 4;

	APP_state & main_state;
	APP_state & recentApp_state;

	APP_state nextState;

	MENU_STATE & mainState_menu;
	MENU_STATE & recent_state;

	MENU_STATE nextMenu_state;
};

