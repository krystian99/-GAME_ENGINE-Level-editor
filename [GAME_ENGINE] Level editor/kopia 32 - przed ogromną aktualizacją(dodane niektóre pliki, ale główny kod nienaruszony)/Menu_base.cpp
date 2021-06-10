#include "Menu_base.h"
#include "Menu_manager.h"
#include <SDL_keyboard.h>

void Menu_base::events()
{
	static const Uint8 * keyboard = SDL_GetKeyboardState(nullptr);

	if (keyboard[SDL_SCANCODE_ESCAPE] && prev_menu != Menu_ID::NONE)
		switch_previous();
}

void Menu_base::switch_previous()
{
	Menu_manager::set_Menu(prev_menu);
}