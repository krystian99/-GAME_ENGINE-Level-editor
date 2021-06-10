#pragma once
#include "Engine_stateID.h"

class Engine_manager
{
public:
	static void Quit();

	static const Engine_state & getState() { return state; }

	static const bool & is_running() { return running; }

	static void setState(const Engine_state & st_chng);
private:
	static Engine_state state;

	static bool running;
};