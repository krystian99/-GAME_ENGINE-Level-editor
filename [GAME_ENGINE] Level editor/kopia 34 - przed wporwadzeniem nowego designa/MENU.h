#pragma once
#include "Menu_start.h"

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
	Menu_start start;
	bool escape_pressed;
};