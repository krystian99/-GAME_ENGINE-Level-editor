#pragma once
#include "MENU_Object.h"
#include "APP_State.h"
#include "Menu_State.h"
#include "Button_Input.h"

class MENU // g³ówna klasa menu
{
public:
	MENU(APP_state & state, APP_state & recent) :
		MainAPP{ state },
		menu_state{ MENU_STATE::START_MENU },
		recentAPP{ recent }
	{}
	~MENU() {}

	void Init();

	const MENU_STATE & getState() const { return menu_state; }

	const std::string & getInput() const { return bt_input.getStrInput(); }

	void setRecentlyState();

	void render();
	void events();
	void events_independent();
private:
	void mSet_Start();
private:
	APP_state & MainAPP;
	APP_state & recentAPP;

	Button_Input bt_input;

	MENU_STATE menu_state;
	MENU_STATE recent_menu_state;

	MENU_Object menu_start;
};

