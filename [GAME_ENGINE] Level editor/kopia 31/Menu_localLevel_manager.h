#pragma once
#include "Menu_localLevel_state.h"

class Menu_localLevel_manager
{
public:
	static const Menu_local_level_state & getState() { return state; }

	static const Menu_local_level_state & get_nextState() { return next_state; }

	static void reset(Menu_local_level_state st);

	static void reset_States();

	static void setState(Menu_local_level_state st_chng);
private:
	static Menu_local_level_state state;
	static Menu_local_level_state next_state;
};