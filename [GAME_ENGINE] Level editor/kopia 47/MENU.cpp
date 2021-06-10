#include "Menu.h"
#include "Menu_manager.h"
#include <SDL_keyboard.h>
#include "Engine_manager.h"

void MENU::events()
{
	switch (Menu_manager::getState())
	{
	case Menu_ID::START:
		start.events();
		break;
	case Menu_ID::LEVEL_MENU:
		level.events();
		break;
	case  Menu_ID::ANIMATION_MENU:
		animation.events();
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
	case Menu_ID::LEVEL_MENU:
		level.events_indp();
		break;
	case Menu_ID::ANIMATION_MENU:
		animation.events_indp();
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
	case Menu_ID::LEVEL_MENU:
		level.render();
		break;
	case  Menu_ID::ANIMATION_MENU:
		animation.render();
		break;
	}
}