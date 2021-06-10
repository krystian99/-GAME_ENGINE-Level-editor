#pragma once
#include "mButton.h"
#include <SDL_video.h>


enum class Environment_Menu_state { NONE, LEVEL_CREATOR, MENU_CREATOR };

class Environment_Menu
{
public:
	Environment_Menu();
	void run();
	~Environment_Menu(){}
private:
	Environment_Menu_state state;
};

