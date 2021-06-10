#pragma once
#include "Texture.h"

class Button
{
public:
	Button(const SDL_Rect & pos);

	virtual void render();
	virtual void events();

	const SDL_Rect & getPOS() const { return position; }

	bool is_clicked() const { return clicked; }
	bool is_mouseOver() const { return mouse_over; }

	//const int & getTX_Width() const { return tX.getWidth(); }
	//const int & getTX_Height() const { return tX.getHeight(); }

	void load_background(std::string path);

	void set_position(const int & render_X, const int & render_Y);

	virtual ~Button() {}
private:
	void mouse_handler();
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	//Texture tX;
	SDL_Rect position;
private:
	bool clicked;
	
	bool mouse_over;

	bool l_bt_pressing;

	int Width;
	int Height;
};