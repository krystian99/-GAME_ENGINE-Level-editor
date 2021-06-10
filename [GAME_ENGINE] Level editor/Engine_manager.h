#pragma once
#include "Engine_stateID.h"

class Engine_manager
{
public:
	static void Quit();

	static const Engine_state & getState() { return state; }

	static const bool & is_running() { return running; }

	static void setState(const Engine_state & st_chng);

	static void set_updateState(Engine_updateState state);
	static Engine_updateState get_updateState() { return update_state; }
private:
	static Engine_state state;
	static Engine_updateState update_state;

	static bool running;
};