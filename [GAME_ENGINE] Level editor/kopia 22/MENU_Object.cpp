#include "MENU_Object.h"

void MENU_Object::addButton(APP_state & app, MENU_STATE & menu, APP_state nextapp, MENU_STATE nextmenu, MENU_STATE & recent_menu, APP_state & recent_app, const SDL_Rect & rt, const std::string & text)
{
	buttons.push_back({ app,nextapp, recent_app, menu, nextmenu, recent_menu });
	buttons.back().setPosition(rt);
	buttons.back().setRenderTEXT("lazy.ttf", text, 50, { 0x0, 0xFF, 0x0, 0xFF });
}

/*void MENU_Object::setButtons(APP_state & app, MENU_STATE & state, const std::vector<OBJ_info> & bts)
{
	buttons.reserve(bts.size());

	for (auto & bt : bts) {
		buttons.push_back({ app, bt.next_appState, state, bt.next_menuState });
		buttons.back().setPosition(bt.rt);
		buttons.back().setRenderTEXT("lazy.ttf", bt.renderTEXT, 50, { 0x0, 0xFF, 0x0, 0xFF });
	}
}*/

void MENU_Object::load_images(std::string str)
{
	for (auto & bt : buttons)
		bt.loadTX(str);
}

void MENU_Object::render(SDL_Renderer * rn)
{
	for (auto & bt : buttons)
		bt.render(rn);
}

void MENU_Object::events_independent()
{
	for (auto & bt : buttons)
		bt.events_independent();
}

void MENU_Object::events()
{
	for (auto & bt : buttons)
		bt.events();
}

MENU_Object::~MENU_Object()
{

}