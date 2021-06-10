#include "Button_load.h"



Button_load::Button_load()
{
}

void Button_load::events()
{
	mouse_handler();
}

void Button_load::render(SDL_Renderer * rn)
{
	Button::render(rn);
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
