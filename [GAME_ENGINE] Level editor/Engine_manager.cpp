#include "Engine_manager.h"

bool Engine_manager::running{ true };
Engine_state Engine_manager::state{ Engine_state::IS_IN_MENU };
Engine_updateState Engine_manager::update_state{ Engine_updateState::NONE };

void Engine_manager::Quit()
{
	running = false;
}

void Engine_manager::setState(const Engine_state & st_chng)
{
	state = st_chng;

	if (state == Engine_state::IS_IN_LC)
		update_state = Engine_updateState::RENDER_PREPARING; // przygotowanie do renderowania -> musi by� ustalony tak�e punkt ko�czenia przygotowa�, by mo�na by�o wyrenderowa� dalej dany modu�
}

void Engine_manager::set_updateState(Engine_updateState state)
{
	update_state = state;
}