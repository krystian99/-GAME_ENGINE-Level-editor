#include "Button_load.h"



Button_load::Button_load()
{
}

void Button_load::events(SDL_Renderer * rn)
{
	Button::render(rn);
	mouse_handler();
}


Button_load::~Button_load()
{
}

void Button_load::onClick()
{
}

void Button_load::onMouseOver()
{
}
