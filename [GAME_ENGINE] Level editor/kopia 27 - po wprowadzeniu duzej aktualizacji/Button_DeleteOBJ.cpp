#include "Button_DeleteOBJ.h"

void Button_DeleteOBJ::render(SDL_Renderer * rn)
{
	Button::render(rn);
}

void Button_DeleteOBJ::events()
{
	//Button::render(rn);
	mouse_handler();
}

void Button_DeleteOBJ::onClick()
{
	edit_State = EditArea_LC_state::DELETING_OBJ;
}

void Button_DeleteOBJ::onMouseOver()
{

}