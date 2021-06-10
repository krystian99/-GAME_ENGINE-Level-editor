#include "Engine_manager.h"

bool Engine_manager::running{ true };
Engine_state Engine_manager::state{ Engine_state::IS_IN_MENU };

void Engine_manager::Quit()
{
	running = false;
}

void Engine_manager::setState(const Engine_state & st_chng)
{
	state = st_chng;
}