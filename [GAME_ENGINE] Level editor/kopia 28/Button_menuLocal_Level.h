#pragma once
#include "Button_menuLocal_base.h"
#include "Button_Menu.h"
#include <vector>
#include <memory>
#include "InputArea.h"

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
	std::unique_ptr<InputArea> input;
};

class Button_SaveAs final : public Button_menuLocal_base
{
public:
	Button_SaveAs(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);

	void events();

	void reset();

	void render();

	~Button_SaveAs() {}
private:
	void onMouseOver();
	void onClick();
private:
	std::unique_ptr<InputArea> input;
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
	void onClick();
	void onMouseOver();
private:
	std::vector<Button_menuLocal_base*> buttons;

	Button_Load load;
	//Button_SaveAs save_as;

	std::unique_ptr<Button_Menu> save; // tylko zapisuje level - nie potrzeba ¿adnego specjalnego interfejsu - wystarczy metoda is_clicked() i renderowany tekst
};