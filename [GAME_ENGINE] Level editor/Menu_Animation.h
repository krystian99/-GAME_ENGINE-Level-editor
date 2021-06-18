#pragma once
#include "Button_Menu.h"
#include "InputArea.h"
#include "Module_base.h"

class Menu_Animation : public Module_base
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