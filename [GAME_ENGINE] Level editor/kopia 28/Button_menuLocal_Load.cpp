#include "Button_menuLocal_Load.h"
#include "LevelEditor_manager.h"
#include "Error.h"

Button_menuLocal_Load::Button_menuLocal_Load(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text }
{
	input = std::unique_ptr<InputArea>{ new InputArea{ {20, 40, 60, 100}, 120, 90, font_path, 20, color_text } }; // trzeba wpisaæ jakieœ dane - najpeirw podstawy pozniej wpiszê
	if (!input)
		Error::throw_Message("Cannot allocate memory at Button_menuLocal_Load!"); // pozniej bêdzie bez konsoli
}

void Button_menuLocal_Load::render()
{
	Button_menuLocal_base::render();
}

void Button_menuLocal_Load::events()
{
	Button_TEXT::events();
}

void Button_menuLocal_Load::onClick()
{
	LevelEditor_manager::loadLevel(input->getStr());
}

void Button_menuLocal_Load::onMouseOver()
{
	// jakieœ operacje
}