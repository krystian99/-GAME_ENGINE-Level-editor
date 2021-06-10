#include "Button_text.h"

Button_TEXT::Button_TEXT(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button{ render_pos },
	text{ start_textX, start_textY , font_path, render_text, size_text, color_text }
{

}

void Button_TEXT::events()
{
	Button::events();
}

void Button_TEXT::render()
{
	Button::render();
	text.render(0, text.getWidth());
}