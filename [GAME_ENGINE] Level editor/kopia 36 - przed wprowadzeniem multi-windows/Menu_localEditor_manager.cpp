#include "Menu_localEditor_manager.h"

Menu_localEditor_state Menu_localEditor_manager::state{ Menu_localEditor_state::IS_IN_LEVEL_MENU };

void Menu_localEditor_manager::setState(Menu_localEditor_state st_chng)
{
	state = st_chng;
}