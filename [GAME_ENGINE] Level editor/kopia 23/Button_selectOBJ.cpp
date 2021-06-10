#include "Button_selectOBJ.h"

void Button_selectOBJ::events()
{
	mouse_handler();
}

void Button_selectOBJ::render(SDL_Renderer * rn)
{
	Button::render(rn);
}

void Button_selectOBJ::onClick()
{
	Button::onClick();
	state = to_chng;
}
