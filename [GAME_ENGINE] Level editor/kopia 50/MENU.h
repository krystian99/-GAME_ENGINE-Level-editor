#pragma once
#include "Menu_start.h"
#include "Menu_Animation.h"
#include "Menu_Level.h"

class MENU
{
public:
	MENU() :
		escape_pressed{ false }
	{}

	void events();
	void events_indp();
	void render();

	~MENU() {}
private:
	Menu_Animation animation;
	Menu_start start;
	Menu_Level level;
	bool escape_pressed;
};