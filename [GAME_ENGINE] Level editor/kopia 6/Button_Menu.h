#pragma once
#include "Button.h"
#include "MENU_Object.h"
#include "APP_State.h"
#include "Menu_State.h"

class Button_Menu final : public Button
{
public:
	Button_Menu(const MENU_STATE & st1, const APP_state & st2);
	//void setNextMenu(const MENU_STATE & st);
	//void setAPP_state(const APP_state & st);

	void events(APP_state & app, MENU_STATE & menu);

	//void setState(MENU_STATE st) { state = st; };
	~Button_Menu();
private:
	void onClick();

	void setNextMenu(MENU_STATE & st);
	void setAPP_state(APP_state & st);

	void mouse_handler();
private:
	//MENU_STATE state;
	APP_state app_state;
	MENU_STATE menu_state;
};

