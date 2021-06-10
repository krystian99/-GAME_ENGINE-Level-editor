#pragma once
#include "Menu_localLevel_state.h"

class Menu_localLevel_manager
{
public:
	static const Menu_local_level_state & getState() { return state; }
	static void setState(Menu_local_level_state st_chng);
private:
	static Menu_local_level_state state;
};