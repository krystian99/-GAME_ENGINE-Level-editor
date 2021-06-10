#include "Button_TEST.h"
#include "Renderer.h"

void Button_TEST::render()
{
	SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::get(), getPOS());
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);

	Button::render(rn);
	TEXT_render();
}

void Button_TEST::events()
{
	mouse_handler();
}

void Button_TEST::onClick()
{
	edit_mainState = EditArea_mainStates::CREATING_OBJ; // zmiana stanu na tworzenie obiektu
	edit_State = EditArea_LC_state::PLACING_OBJ;
}

void Button_TEST::onMouseOver()
{

}

void Button_TEST::TEXT_render()
{
	const SDL_Rect * rt = getPOS();

	text.render(Renderer::get(), rt->x + FRAME_SIZE, text.getWidth());
}
