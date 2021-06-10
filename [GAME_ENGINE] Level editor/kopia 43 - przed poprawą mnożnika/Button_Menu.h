#pragma once
#include "Button_TEXT.h"

class Button_Menu : public Button_TEXT
{
public:
	Button_Menu(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);

	void events();
	void render();

	~Button_Menu() {}
protected:
	void onClick();
	void onMouseOver();
private:
	//void moveText(const int & size);
};