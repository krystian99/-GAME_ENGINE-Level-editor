#include "Menu.h"
#include "Menu_manager.h"
#include <SDL_keyboard.h>
#include "Engine_manager.h"

MENU::MENU()
{
	Menu_manager::INIT(&animation, &start, &level);
}

void MENU::events()
{
	Menu_manager::getModule()->events();
}

void MENU::events_indp()
{
	Menu_manager::getModule()->events_indp();
}

void MENU::render()
{
	Menu_manager::getModule()->render();
}