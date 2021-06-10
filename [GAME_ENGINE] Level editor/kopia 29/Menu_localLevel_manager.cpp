#include "Menu_localLevel_manager.h" // dla przycisku level

Menu_local_level_state Menu_localLevel_manager::state{ Menu_local_level_state::NONE };

void Menu_localLevel_manager::setState(Menu_local_level_state st_chng)
{
	state = st_chng;
}