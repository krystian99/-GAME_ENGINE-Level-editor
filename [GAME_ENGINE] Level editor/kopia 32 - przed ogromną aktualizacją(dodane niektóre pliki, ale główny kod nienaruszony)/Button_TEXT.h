#pragma once
#include "Button.h"
#include "Text.h"
#include <string>

class Button_TEXT : public Button
{
public:
	Button_TEXT(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);

	virtual void events();
	virtual void render();

	//Text * getText() { return &text; }

	virtual ~Button_TEXT() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	Text text;
};