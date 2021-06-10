#include "Button_menuLocal_Level.h"
#include "Menu_localLevel_manager.h"
#include "LevelEditor_manager.h"
#include "Error.h"

Button_menuLocal_Level::Button_menuLocal_Level(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text },
	load{ {22, 57, 97, 25}, start_textX, start_textY + (2 *render_pos.h), font_path, "LOAD", size_text, color_text }
{
	save = std::unique_ptr<Button_Menu>{ new Button_Menu{ { position.x, position.y + position.h, position.w + 20, position.h }, start_textX, start_textY + position.h, font_path, "SAVE LEVEL", 25, { 255 } } };
	if (!save)
		throw Error::throw_Message("Cannot allocate memory at ButtonMenu_local_level!");

	/*buttons = {
		new Button_menuLocal_SaveAs{ { 20, 30, 50, 60 }, 30, 50, font_path, "SAVE AS: ", 20, color_text }
	};*/
}


void Button_menuLocal_Level::render()
{
	Button_menuLocal_base::render();

	if (is_active()) {
		save->render();
		load.render();
		//save_as.render();

		for (auto & button : buttons)
			button->render();
	}
}

void Button_menuLocal_Level::events()
{
	Button_menuLocal_base::events();

	if (is_active()) {
		save->events();
		load.events();
		//save_as.render();

		if (save->is_clicked())
			LevelEditor_manager::setSate(LevelEditor_state::SAVE_CURRENT_LEVEL);
		/*switch (Menu_localLevel_manager::getState())
		{
		case Menu_local_level_state::IS_IN_LOAD_MENU:
			break;
		case Menu_local_level_state::IS_IN_SAVE_AS_MENU:
			break;
		}*/
	}
}

void Button_menuLocal_Level::reset()
{
	Button_menuLocal_base::reset();
	load.reset();
	//save_as.reset();
}

void Button_menuLocal_Level::onClick()
{
	if (is_active())
		reset();
	else 
		Button_menuLocal_base::onClick();
}

void Button_menuLocal_Level::onMouseOver()
{

}

Button_Load::Button_Load(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text }
{
	input = std::unique_ptr<InputArea>{ new InputArea{ { 20, 40, 60, 100 }, 120, 90, font_path, 20, color_text } }; // trzeba wpisaæ jakieœ dane - najpeirw podstawy pozniej wpiszê
	if (!input)
		Error::throw_Message("Cannot allocate memory at Button_menuLocal_Load!"); // pozniej bêdzie bez konsoli
}

void Button_Load::render()
{
	Button_menuLocal_base::render();
	if (is_active()) {
		input->render();
	}
}

void Button_Load::reset()
{
	Button_menuLocal_base::reset();
	input->reset();
}

void Button_Load::events()
{
	Button_menuLocal_base::events();
	if (is_active()) {
		input->events();
		if (input->is_clicked())
			input->setCurrent(true);
	}
}

void Button_Load::onClick()
{
	if (is_active()) {
		if (LevelEditor_manager::loadLevel(input->getStr()))
			reset();
		else Button_menuLocal_base::onClick();
	}
	else Button_menuLocal_base::onClick();
}

void Button_Load::onMouseOver()
{
	// jakieœ operacje
}

Button_SaveAs::Button_SaveAs(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text }
{
	// inicjuj dane
}

void Button_SaveAs::events()
{
	Button_menuLocal_base::events();
}

void Button_SaveAs::reset()
{

}

void Button_SaveAs::render()
{
	Button_menuLocal_base::render();
}

void Button_SaveAs::onMouseOver()
{
	// jakies operacje
}

void Button_SaveAs::onClick()
{
	if (!input->is_empty())
		LevelEditor_manager::saveLevel_As(input->getStr());
}