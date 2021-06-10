#pragma once
#include "Menu_base.h"
#include "Button_Menu.h"
#include "InputArea.h"

class Menu_Animation : public Menu_base
{
public:
	Menu_Animation();

	void events();
	void events_indp();
	void render();

	~Menu_Animation() {}
private:
	Button_Menu newConfig, loadConfig;

	InputArea input_animName, input_amountOf_frames;
};