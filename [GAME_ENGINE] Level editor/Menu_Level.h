#pragma once
#include <string>
#include "InputArea.h"
#include "Folder_button.h"
#include "Image.h"
#include "Button.h"
#include "Module_base.h"

class Menu_Level : public Module_base
{
public:
	Menu_Level();

	void events();
	void events_indp();
	void render();

	~Menu_Level() {}
private:
	Object data[3][3];
	
	Image plansza;

	Image kolko;
};