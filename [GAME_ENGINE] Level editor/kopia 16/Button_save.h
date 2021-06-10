#pragma once
#include "Button.h"
class Button_save : public Button
{
public:
	Button_save();
	void events();

	void render(SDL_Renderer * rn);
	~Button_save();
private:
	void onClick();
	void onMouseOver();
};