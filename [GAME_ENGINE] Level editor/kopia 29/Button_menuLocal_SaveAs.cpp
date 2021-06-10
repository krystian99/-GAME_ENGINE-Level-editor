#include "Button_menuLocal_SaveAs.h"
#include "LevelEditor_manager.h"


Button_menuLocal_SaveAs::Button_menuLocal_SaveAs(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text }
{
	// inicjuj dane
}

void Button_menuLocal_SaveAs::events()
{
	Button_menuLocal_base::events();
}

void Button_menuLocal_SaveAs::render()
{
	Button_menuLocal_base::render();
}

void Button_menuLocal_SaveAs::onMouseOver()
{
	// jakies operacje
}

void Button_menuLocal_SaveAs::onClick()
{
	if (!input->is_empty())
		LevelEditor_manager::saveLevel_As(input->getStr());
}