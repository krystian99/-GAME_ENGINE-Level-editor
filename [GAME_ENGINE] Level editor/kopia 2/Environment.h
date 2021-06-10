#pragma once
#include "ScrollBar.h"
//#include "EditionArea.h"

enum class Event_state { NONE, BUTTON_CLICKED };

class Environment
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
	//EditionArea edit_Area;
};

