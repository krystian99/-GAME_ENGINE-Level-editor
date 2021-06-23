#include "Menu_manager.h"

Menu_ID Menu_manager::menu_id{ Menu_ID::START };

Menu_Animation* Menu_manager::menu_anim;
Menu_start* Menu_manager::menu_start;
Menu_Level* Menu_manager::menu_level;
Module_base* Menu_manager::currentModule;

void Menu_manager::set_Menu(Menu_ID ID)
{
	menu_id = ID;

	switch (ID)
	{
	case Menu_ID::START:
		currentModule = menu_start;
		break;
	case Menu_ID::LEVEL_MENU:
		currentModule = menu_level;
		break;
	case Menu_ID::ANIMATION_MENU:
		currentModule = menu_anim;
		break;
	}
}

void Menu_manager::INIT(Menu_Animation* anim, Menu_start* start, Menu_Level* level)
{
	menu_anim = anim;
	menu_start = start;
	menu_level = level;

	currentModule = start;
}
