#include "Button_save.h"

void Button_save::events()
{
	mouse_handler();
}


void Button_save::render(SDL_Renderer * rn)
{
	Button::render(rn);
}

void Button_save::onClick()
{
	Button::onClick();
}

void Button_save::onMouseOver()
{

}
