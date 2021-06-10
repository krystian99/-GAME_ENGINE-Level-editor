#pragma once
#include <SDL_rect.h>

class Base_OBJ
{
public:
	Base_OBJ() :
		clicked{ false },
		l_bt_pressing{ false },
		mouse_over{ false }
	{}

	virtual void render() = 0;
	virtual void events() = 0;

	bool is_clicked() const { return clicked; }
	bool mouse_is_Over() const { return mouse_over; }

	void set_position(const int & render_X, const int & render_Y);

	virtual ~Base_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
private:
	void mouse_handler();
protected:
	SDL_Rect render_position;
private:
	bool clicked;
	bool mouse_over;
	bool l_bt_pressing;
};