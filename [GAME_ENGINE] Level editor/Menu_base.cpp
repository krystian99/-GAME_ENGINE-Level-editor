#include "Menu_base.h"
#include "Menu_manager.h"
#include <SDL_keyboard.h>

void Menu_base::switch_previous()
{
	Menu_manager::set_Menu(prev_menu);
}