#include "MENU_Object.h"



MENU_Object::MENU_Object()
{
}

void MENU_Object::setButtons(const std::vector<OBJ_info> & bts)
{
	/*buttons.resize(bts.size());
	for (int i = 0; i < bts.size(); i++) {
		buttons[i].setPosition(bts[i].rt);
		buttons[i].setNext(bts[i].next_menu);
		buttons[i].loadTX("str");
	}*/
	for (auto & bt : bts) {
		buttons.push_back(Button_Menu{ bt.next_menuState, bt.next_appState });
		buttons[buttons.size() - 1].setPosition(bt.rt);
	}
}

void MENU_Object::events(APP_state & app_state, MENU_STATE & menu_state)
{

}

void MENU_Object::events(APP_state & app, MENU_STATE & menu)
{
	for (auto & bt : buttons)
		bt.events(app, menu);
}

void MENU_Object::render(SDL_Renderer * rn)
{
	for (auto & bt : buttons)
		bt.render(rn);
}


MENU_Object::~MENU_Object()
{

}