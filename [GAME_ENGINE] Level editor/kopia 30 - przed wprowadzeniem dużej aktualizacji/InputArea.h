#pragma once
#include <string>
#include <SDL_render.h>
#include "Text.h"
#include "Texture.h"

class InputArea
{
public:
	InputArea(const SDL_Rect & pos, const int & startX, const int & startY, const std::string & font_path, int size_text, const SDL_Color & color_text);

	void render();
	void events();

	void load_background(const std::string & d);

	const std::string & getStr() const { return input; }

	bool is_clicked() const { return clicked; }

	void reset();

	const bool & is_empty() const { return empty; }

	void setCurrent(bool x);

	~InputArea() {}
private:
	void addBack(const char & c);

	void updateTEXT();

	void getLiters();
	void getOthers();
	void getDigits();

	void mouse_handler();
private:
	std::string input;

	SDL_Rect position;

	Text text;

	Texture background;

	//bool l_bt_pressing;
	//bool capslock_pressing;

	bool backspace_pressing;

	bool empty;

	bool toggled_CapsLock;

	bool clicked;

	bool current;
};