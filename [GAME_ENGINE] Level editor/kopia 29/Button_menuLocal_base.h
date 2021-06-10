#pragma once
#include "Button_TEXT.h"

class Button_menuLocal_base : public Button_TEXT
{
public:
	Button_menuLocal_base(const SDL_Rect & render_pos, int start_textX, int start_textY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);
	
	virtual void events();
	virtual void render();
	
	virtual void reset();

	//void setActive(bool act);

	const bool & is_active() const { return active; }

	~Button_menuLocal_base() {}
protected:
	virtual void onClick();
	virtual void onMouseOver() = 0;
private:
	bool active;
};