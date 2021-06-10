#pragma once
#include "Button_menuLocal_base.h"

class Button_menuLocal_Objects : public Button_menuLocal_base
{
public:
	Button_menuLocal_Objects(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);
	
	void events();
	void render();

	~Button_menuLocal_Objects() {}
};