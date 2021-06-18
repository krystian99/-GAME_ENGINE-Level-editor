#pragma once
#include "Menu_start.h"
#include "Menu_Animation.h"
#include "Menu_Level.h"
#include "Module_base.h"

// klasa zarz�dzaj�ca Menusami
class MENU : public Module_base
{
public:
	MENU();

	void events();
	void events_indp();
	void render();

	~MENU() {}
private:
	Menu_Animation animation;
	Menu_start start;
	Menu_Level level;

	bool escape_pressed{ false };
};