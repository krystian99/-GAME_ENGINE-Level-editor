#pragma once
#include "Engine_stateID.h"
#include "Module_base.h"
#include "LevelCreator.h"
#include "MENU.h"
#include "Animation_management.h"
#include "Script_Editor.h"

class Engine_manager
{
public:
	static void INIT(MENU* menu, LevelCreator* lc, Animation_management* am, Script_Editor* se);

	static void Quit();

	static const Engine_state & getState() { return state; }

	static Module_base* getModule() { return currentModule; }

	static const bool & is_running() { return running; }

	static void setState(const Engine_state & st_chng);

	static void set_updateState(Engine_updateState state);
	static Engine_updateState get_updateState() { return update_state; }
private:
	static Engine_state state;
	static Engine_updateState update_state;

	static Module_base* currentModule;

	static LevelCreator* level;
	static MENU* menu;
	static Animation_management* anim;
	static Script_Editor* sc_edit;

	static bool running;
};