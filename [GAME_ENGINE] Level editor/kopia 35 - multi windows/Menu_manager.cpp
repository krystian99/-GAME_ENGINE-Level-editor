#include "Menu_manager.h"

Menu_ID Menu_manager::menu_id{ Menu_ID::START };

void Menu_manager::set_Menu(Menu_ID ID)
{
	menu_id = ID;
}