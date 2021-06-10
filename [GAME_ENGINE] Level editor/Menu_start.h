#pragma once
#include <string>
#include "Image.h"
#include "Text.h"
#include "Button.h"

class Menu_start
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

	Button levelEditor_button, animationsEditor_button, Script_editor_button;
};