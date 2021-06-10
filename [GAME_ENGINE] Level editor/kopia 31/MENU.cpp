#include "Menu.h"
#include "Menu_manager.h"
#include <SDL_keyboard.h>
#include "Engine_manager.h"

void MENU::events()
{
	static const Uint8 * keyboard = SDL_GetKeyboardState(nullptr);

	/*if (keyboard[SDL_SCANCODE_ESCAPE])
		escape_pressed = true;

	else if (!keyboard[SDL_SCANCODE_ESCAPE] && escape_pressed) {
		escape_pressed = false;
		switch (Menu_manager::getState())
		{
		case Menu_ID::START:
			Engine_manager::Quit();
			break;
		}
	}*/

	switch (Menu_manager::getState())
	{
	case Menu_ID::START:
		start.events();
		break;
	}
}

void MENU::events_indp()
{
	switch (Menu_manager::getState())
	{
	case Menu_ID::START:
		start.events_indp();
		break;
	}
}

void MENU::render()
{
	switch (Menu_manager::getState())
	{
	case Menu_ID::START:
		start.render();
		break;
	}
}