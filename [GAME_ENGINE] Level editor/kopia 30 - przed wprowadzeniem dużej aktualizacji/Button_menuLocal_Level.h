#pragma once
#include "Button_menuLocal_base.h"
#include "Button_Menu.h"
#include <vector>
#include <memory>
#include "InputArea.h"
#include "Menu_localLevel_state.h"

class Button_Load final : public Button_menuLocal_base {
public:
	Button_Load(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);

	void render();
	
	void reset();
	void events();

	~Button_Load() {}
private:
	void onClick();
	void onMouseOver();
private:
	InputArea input;
};

class Button_SaveAs final : public Button_menuLocal_base
{
public:
	Button_SaveAs(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);

	void events();

	void reset();
	void events_indp();
	void render();

	~Button_SaveAs() {}
private:
	void onMouseOver();
	void onClick();
private:
	InputArea input;
};

class Button_menuLocal_Level : public Button_menuLocal_base // interfejs zamkniêty w tej klasie
{
public:
	Button_menuLocal_Level(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);

	void render();
	void events();

	void reset();

	~Button_menuLocal_Level() {}
private:
	void reset(Menu_local_level_state st); // resetuj z wyj¹tkiem obiektu ktory jest argumentem

	void onClick();
	void onMouseOver();
private:
	Button_Load load;
	Button_SaveAs save_as;
	Button_Menu save;
};