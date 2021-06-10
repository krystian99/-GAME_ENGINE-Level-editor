#pragma once
#include "Menu_localEditor_state.h"

class Menu_localEditor_manager
{
public:
	static void setState(Menu_localEditor_state st_chng);
	static const Menu_localEditor_state & getState() { return state; }
private:
	static Menu_localEditor_state state;
};