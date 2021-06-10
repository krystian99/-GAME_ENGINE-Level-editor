#include "Button_menuLocal_Level.h"
#include "Menu_localLevel_manager.h"
#include "LevelEditor_manager.h"
#include "Error.h"

Button_menuLocal_Level::Button_menuLocal_Level(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text },
	save{ { render_pos.x, render_pos.y + render_pos.h, render_pos.w, render_pos.h }, start_textX, start_textY + render_pos.h, font_path, "SAVE", size_text, color_text },
	save_as{ { render_pos.x, render_pos.y + 2 * render_pos.h, render_pos.w, render_pos.h }, start_textX, start_textY + 2 * render_pos.h, font_path, "SAVE AS", size_text, color_text },
	load{ { render_pos.x, render_pos.y + 3 * render_pos.h, render_pos.w, render_pos.h }, start_textX, start_textY + 3 * render_pos.h, font_path, "LOAD", size_text, color_text }
{}


void Button_menuLocal_Level::render()
/*
	Renderuje
*/
{
	Button_menuLocal_base::render();

	if (is_active()) {
		save.render();
		load.render();
		save_as.render();
	}
}

void Button_menuLocal_Level::events()
{
	Button_menuLocal_base::events();

	if (is_active()) {
		save.events();
		load.events();
		save_as.events();

		switch (Menu_localLevel_manager::getState())
		{
		case Menu_local_level_state::RESET:
			reset(Menu_localLevel_manager::get_nextState());
			break;
		}

		if (save.is_clicked())
			LevelEditor_manager::set_Management_state(LevelEditor_Management_state::SAVE_CURRENT_LEVEL);
	}
}

void Button_menuLocal_Level::reset()
{
	Button_menuLocal_base::reset();
	load.reset();
	save_as.reset();
}

// Zresetuj wszystkie przyciski oprócz podanego w argumencie
void Button_menuLocal_Level::reset(Menu_local_level_state st)
{
	switch (st)
	{
	case Menu_local_level_state::IS_IN_LOAD_MENU:
		save_as.reset();
		break;
	case Menu_local_level_state::IS_IN_SAVE_AS_MENU:
		load.reset();
		break;
	}
	Menu_localLevel_manager::reset_States(); // resetuje wszystkie stany
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
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text },
	input{ { render_pos.x + render_pos.w, render_pos.y, render_pos.w, render_pos.h }, render_pos.x + render_pos.w + 5, start_textY, font_path, size_text, color_text }
{}

void Button_Load::render()
{
	Button_menuLocal_base::render();
	if (is_active())
		input.render();
}

void Button_Load::reset()
{
	Button_menuLocal_base::reset();
	input.reset();
}

void Button_Load::events()
{
	Button_menuLocal_base::events();
	if (is_active())
		input.events();
}

void Button_Load::onClick()
{
	if (is_active()) {
		if (LevelEditor_manager::loadLevel(input.getStr()))
			reset();
	}
	else { 
		Menu_localLevel_manager::reset(Menu_local_level_state::IS_IN_LOAD_MENU);
		input.setCurrent(true);
	}

	Button_menuLocal_base::onClick();
}

void Button_Load::onMouseOver()
{
	
}

Button_SaveAs::Button_SaveAs(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Button_menuLocal_base{ render_pos, start_textX, start_textY, font_path, render_text, size_text, color_text },
	input{ {render_pos.x + render_pos.w, render_pos.y, render_pos.w, render_pos.h}, render_pos.x + render_pos.w + 5, start_textY, font_path, size_text, color_text }
{}

void Button_SaveAs::events()
{
	Button_menuLocal_base::events();
	if (is_active())
		input.events();
}

void Button_SaveAs::reset()
{
	Button_menuLocal_base::reset();
	input.reset();
}

void Button_SaveAs::events_indp()
{

}

void Button_SaveAs::render()
{
	Button_menuLocal_base::render();
	if (is_active())
		input.render();
}

void Button_SaveAs::onMouseOver()
{
	
}

void Button_SaveAs::onClick()
{
	if (is_active()) {
		if (!input.is_empty())
			LevelEditor_manager::saveLevel_As(input.getStr());
	}
	else { 
		Menu_localLevel_manager::reset(Menu_local_level_state::IS_IN_SAVE_AS_MENU);
		input.setCurrent(true); 
	}

	Button_menuLocal_base::onClick();
}