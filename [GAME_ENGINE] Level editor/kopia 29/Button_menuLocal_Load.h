#pragma once
#include "Button_menuLocal_base.h"
#include "InputArea.h"
#include <memory>

class Button_menuLocal_Load : public Button_menuLocal_base
{
public:
	Button_menuLocal_Load(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);

	void render();
	void events();

	~Button_menuLocal_Load() {}
private:
	void onClick();
	void onMouseOver();
private:
	std::unique_ptr<InputArea> input;
};