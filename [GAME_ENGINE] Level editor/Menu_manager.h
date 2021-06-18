#pragma once
#include "Menu_ID.h"
#include "Menu_start.h"
#include "Menu_Animation.h"
#include "Menu_Level.h"

class Menu_manager
{
	friend class MENU;
public:
	static void set_Menu(Menu_ID id);

	static const Menu_ID & getState() { return menu_id; }
private:
	static void INIT(Menu_Animation* menu_anim, Menu_start* menu_start, Menu_Level* menu_level);
	static Module_base* getModule() { return currentModule; }
private:
	static Menu_ID menu_id;

	static Menu_Animation* menu_anim;
	static Menu_start* menu_start;
	static Menu_Level* menu_level;

	static Module_base* currentModule;
};