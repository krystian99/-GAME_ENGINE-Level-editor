#pragma once
#include <string>
#include "Image.h"
#include "Text.h"
#include "Button.h"
#include "Module_base.h"

class Menu_start : public Module_base
{
public:
	Menu_start();

	void events();
	void events_indp();
	void render();

	~Menu_start() {}
private:
	Text copyright;

	Image project_name;

	Button Exit;

	Button animationsEditor_button, Script_editor_button;

	Button start_game;
};