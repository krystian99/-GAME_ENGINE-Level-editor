#include "Menu_localLevel_manager.h" // dla przycisku level

Menu_local_level_state Menu_localLevel_manager::state{ Menu_local_level_state::NONE };
Menu_local_level_state Menu_localLevel_manager::next_state{ Menu_local_level_state::NONE };

void Menu_localLevel_manager::reset(Menu_local_level_state st)
{
	next_state = st;
	state = Menu_local_level_state::RESET;
}

void Menu_localLevel_manager::reset_States()
{
	state = {};
	next_state = {};
}

void Menu_localLevel_manager::setState(Menu_local_level_state st_chng)
{
	state = st_chng;
}