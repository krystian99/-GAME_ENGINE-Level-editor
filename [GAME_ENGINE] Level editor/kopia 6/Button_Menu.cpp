#include "Button_Menu.h"
#include "Mouse.h"

void Button_Menu::mouse_handler()
{
	Button::mouse_handler();
	const SDL_Rect * position = Button::getPOS();
	if (Mouse::getMousePOSx() >= position->x && Mouse::getMousePOSx() <= position->x + position->w
		&& Mouse::getMousePOSy() >= position->y && Mouse::getMousePOSy() <= position->y + position->h)
	{

	}
}


Button_Menu::Button_Menu(const MENU_STATE & st1, const APP_state & st2)
{

}

void Button_Menu::onClick()
{

}

void Button_Menu::events(APP_state & app, MENU_STATE & menu)
{
	mouse_handler();
	if (Button::is_clicked())
	{
		app = app_state;
		menu = menu_state;
	}
}

Button_Menu::~Button_Menu()
{
}

void Button_Menu::setNextMenu(MENU_STATE & st)
{
	st = menu_state;
}

void Button_Menu::setAPP_state(APP_state & st)
{
	st = app_state;
}
