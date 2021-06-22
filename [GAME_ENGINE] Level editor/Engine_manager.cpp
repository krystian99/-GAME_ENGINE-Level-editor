#include "Engine_manager.h"

bool Engine_manager::running{ true };
Engine_state Engine_manager::state{ Engine_state::IS_IN_MENU };
Engine_updateState Engine_manager::update_state{ Engine_updateState::NONE };
Module_base* Engine_manager::currentModule{};

LevelCreator* Engine_manager::level;
MENU* Engine_manager::menu;
Animation_management* Engine_manager::anim;
Script_Editor* Engine_manager::sc_edit;

void Engine_manager::INIT(MENU* m, LevelCreator* lc, Animation_management* am, Script_Editor* se)
{
	level = lc;
	menu = m;
	anim = am;
	sc_edit = se;

	currentModule = menu;
}

void Engine_manager::Quit()
{
	running = false;
}

bool Engine_manager::is_inState(Engine_state s)
{
	return false;
}

void Engine_manager::setState(const Engine_state & st_chng)
{
	state = st_chng;

	if (state == Engine_state::IS_IN_LC)
		update_state = Engine_updateState::RENDER_PREPARING; // przygotowanie do renderowania -> musi byæ ustalony tak¿e punkt koñczenia przygotowañ, by mo¿na by³o wyrenderowaæ dalej dany modu³

	switch (st_chng)
	{
	case Engine_state::IS_IN_MENU:
		currentModule = menu;
		break;
	case Engine_state::IS_IN_LC:
		currentModule = level;
		break;
	case Engine_state::IS_IN_ANIMATION_MANAGEMENT:
		currentModule = anim;
		break;
	case Engine_state::IS_IN_SCRIPT_EDITOR:
		currentModule = sc_edit;
		break;
	}
}

void Engine_manager::set_updateState(Engine_updateState state)
{
	update_state = state;
}