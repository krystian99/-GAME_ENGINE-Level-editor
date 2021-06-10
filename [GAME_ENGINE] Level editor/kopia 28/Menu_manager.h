#pragma once
#include "Menu_ID.h"

class Menu_manager
{
public:
	static void set_Menu(Menu_ID id);

	static const Menu_ID & getState() { return menu_id; }
private:
	static Menu_ID menu_id;
	//static Menu_ID menu_previous;
};