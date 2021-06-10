#include "Button_Menu.h"

void Button_Menu::onClick()
{
	
}

void Button_Menu::onMouseOver()
{
	
}


Button_Menu::Button_Menu(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_TEXT{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text }
{
	//tX.loadFromFile("");
}

void Button_Menu::events()
{
	Button_TEXT::events();
}

void Button_Menu::render()
{
	Button_TEXT::render();
}