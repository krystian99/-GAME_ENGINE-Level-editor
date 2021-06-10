#pragma once
#include "Texture.h"

class Button
{
public:
	Button(const SDL_Rect & pos);
	Button(const SDL_Rect & pos, const std::string & texture);
	Button(const std::string & texture);

	virtual void render();
	void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);

	virtual void events();

	const SDL_Rect & getPOS() const { return position; }

	bool is_clicked() const { return clicked; }
	bool is_mouseOver() const { return mouse_over; }

	const Texture & getTX() const { return tX; } // zwr�� textur� w celu uzyskania informacji o szeroko�ci lub d�ugo�ci

	void set_texture(const std::string & path);

	void update_position(const int & renderX, const int & renderY);
	void set_position(const SDL_Rect & pos);

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
};