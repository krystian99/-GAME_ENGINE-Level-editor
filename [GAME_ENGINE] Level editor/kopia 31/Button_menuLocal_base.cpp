#include "Button_menuLocal_base.h"
#include "Renderer.h" // dla testu

Button_menuLocal_base::Button_menuLocal_base(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_TEXT{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text },
	active{ false }
{}

void Button_menuLocal_base::events()
{
	Button_TEXT::events();
}

void Button_menuLocal_base::render()
{
	Button_TEXT::render();
	SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::get(), &position);
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}

void Button_menuLocal_base::reset()
{
	active = false;
}

void Button_menuLocal_base::onClick()
{
	active = !active;
}