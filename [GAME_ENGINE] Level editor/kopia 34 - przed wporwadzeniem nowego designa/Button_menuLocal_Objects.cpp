#include "Button_menuLocal_Objects.h"

Button_menuLocal_Objects::Button_menuLocal_Objects(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text }
{}

void Button_menuLocal_Objects::events()
{
	Button_menuLocal_base::events();
}

void Button_menuLocal_Objects::render()
{
	Button_menuLocal_base::render();
}