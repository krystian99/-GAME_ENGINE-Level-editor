#pragma once
#include "Texture.h"

class Button
{
public:
	Button(const SDL_Rect & pos);

	Button(const SDL_Rect & pos, const std::string & texture);

	virtual void render();
	virtual void events();

	const SDL_Rect & getPOS() const { return position; }

	bool is_clicked() const { return clicked; }
	bool is_mouseOver() const { return mouse_over; }

	const Texture & getTX() const { return tX; } // zwróæ texturê w celu uzyskania informacji o szaerokoœci lub d³ugoœci

	void set_texture(const std::string & path);

	void set_position(const int & render_X, const int & render_Y);

	virtual ~Button() {}
private:
	void mouse_handler();
protected:
	virtual void onMouseOver();
	virtual void onClick();
protected:
	Texture tX;
	SDL_Rect position;
private:
	bool clicked;
	
	bool mouse_over;

	bool l_bt_pressing;

	int Width;
	int Height;
};