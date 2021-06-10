#pragma once
#include "Button.h"
class Button_load : public Button
{
public:
	Button_load();
	void events(SDL_Renderer * rn);
	~Button_load();
private:
	void onClick();
	void onMouseOver();
};

