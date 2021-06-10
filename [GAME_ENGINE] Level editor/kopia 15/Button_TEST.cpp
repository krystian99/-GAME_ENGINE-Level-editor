#include "Button_TEST.h"

void Button_TEST::events(SDL_Renderer * rn)
{
	mouse_handler();
	Button::render(rn);
	SDL_SetRenderDrawColor(rn, 255, 0, 0, 255);
	SDL_RenderDrawRect(rn, getPOS());
	SDL_SetRenderDrawColor(rn, 255, 255, 255, 255);
	TEXT_render(rn);
}

void Button_TEST::onClick()
{
	edit_mainState = EditArea_mainStates::CREATING_OBJ; // zmiana stanu na tworzenie obiektu
	edit_State = EditArea_LC_state::PLACING_OBJ;
}

void Button_TEST::onMouseOver()
{

}

void Button_TEST::TEXT_render(SDL_Renderer * rn)
{
	const SDL_Rect * rt = getPOS();

	text.render(rn, rt->x + FRAME_SIZE, text.getWidth());
}
