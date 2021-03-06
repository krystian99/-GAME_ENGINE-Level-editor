#pragma once
#include "Menu_ID.h"

class Menu_base
{
public:
	Menu_base(Menu_ID prev) :
		prev_menu{ prev }
	{}
	Menu_base() :
		prev_menu{ Menu_ID::NONE }
	{}

	~Menu_base() {}
private:
	void switch_previous();
private:
	Menu_ID prev_menu;
};