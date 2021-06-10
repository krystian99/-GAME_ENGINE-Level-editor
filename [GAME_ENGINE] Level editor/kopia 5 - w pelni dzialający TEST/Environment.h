#pragma once
//#include "ScrollBar.h"
#include "LevelCreator.h"
#include "Environment_Menu.h"

enum class Event_state { NONE, BUTTON_CLICKED };

class Environment // g³ówna klasa steruj¹ca/operuj¹ca
{
public:
	Environment();
	void run();
	~Environment();
private:
	void events();

	void Init();

	void start_render();

	void renderAll();

	void switchAppState();
private:
	Event_state state;
	ScrollBar sbDynamic, sbKey, sbStatic; // sb - scroll bar
	//LevelEditor edit_Area;
};

