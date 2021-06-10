#pragma once
#include "Texture.h"

class Button // musi zosta� w przysz�o�ci zmienione - jak na razie zajmuje si� wa�niejszymi sprawami(14.07.2016r.) 
{
protected:
	using Function = void(*)();
public:
	Button(const SDL_Rect & pos);
	Button(const SDL_Rect & pos, const std::string & texture);
	Button(const std::string & texture);
	Button(const std::string & texture, Function on_click);
	Button(const std::string & texture, Function on_click, Function on_mouse_over);
	Button(const SDL_Rect & pos, const std::string & texture, Function on_click);
	Button(const SDL_Rect & pos, const std::string & texture, Function on_click, Function on_mouse_over);

	virtual void render();
	virtual void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);

	virtual void events();

	const SDL_Rect & getPOS() const { return position; }

	bool is_clicked() const { return clicked; }
	bool is_mouseOver() const { return mouse_over; }
	bool is_selected() const { return selected; }

	const Texture & getTX() const { return tX; } // zwr�� textur� w celu uzyskania informacji o szeroko�ci lub d�ugo�ci

	void reset();

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
	Texture tX; // background texture
	SDL_Rect position{}; // pozycja do renderowania
private:
	Function on_click_func{ nullptr };
	Function on_mouse_over_func{ nullptr };

	bool clicked{ false };
	
	bool selected{ false };

	bool mouse_over{ false };

	bool l_bt_pressing{ false };
};