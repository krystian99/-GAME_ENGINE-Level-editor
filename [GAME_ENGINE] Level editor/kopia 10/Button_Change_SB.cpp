#include "Button_Change_SB.h"

void Button_Change_SB::Init(const SDL_Rect & rt)
{
	setPosition(rt);
}

void Button_Change_SB::events(SDL_Renderer * rn)
{
	renderALL(rn);
	mouse_handler();
}

void Button_Change_SB::renderALL(SDL_Renderer * rn)
{
	Button::render(rn);
	text.render(rn, textPOS.x + FRAME_SIZE, text.getWidth());
}

void Button_Change_SB::onClick()
{
	current = next;
}

void Button_Change_SB::onMouseOver()
{

}
