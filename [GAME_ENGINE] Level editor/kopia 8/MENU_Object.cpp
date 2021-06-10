#include "MENU_Object.h"

void MENU_Object::setButtons(APP_state & app, MENU_STATE & state, const std::vector<OBJ_info> & bts)
{
	buttons.reserve(bts.size());

	for (auto & bt : bts) {
		buttons.push_back({ app, bt.next_appState, state, bt.next_menuState });
		buttons[buttons.size() - 1].setPosition(bt.rt);
		buttons[buttons.size() - 1].setRenderTEXT("lazy.ttf", bt.renderTEXT, 50, { 0x0, 0xFF, 0x0, 0xFF });
	}
}

void MENU_Object::load_images(std::string str)
{
	for (auto & bt : buttons)
		bt.loadTX(str);
}

void MENU_Object::events(SDL_Renderer * rn)
{
	for (auto & bt : buttons)
		bt.events(rn);
}

MENU_Object::~MENU_Object()
{

}