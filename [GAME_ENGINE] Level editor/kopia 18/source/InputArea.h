#pragma once
#include <string>
#include <SDL_render.h>
#include <cctype>
#include "Font.h"
#include "Texture.h"

class InputArea
{
public:
	InputArea() :
		toggled_CapsLock{ false },
		l_bt_pressing{ false },
		capslock_pressing{ false },
		backspace_pressing{ false },
		empty{ true }
	{}

	void Init(const SDL_Rect & rt, const int & size, const SDL_Color & color);

	void render(SDL_Renderer * rn);
	void events();

	void loadTX(const std::string & d);

	const std::string & getStr() const { return input; }

	const bool & is_empty() const { return empty; }

	void set_TextSize(const int & size);
	void set_TextColor(const SDL_Color & color);

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
	SDL_Rect textPOS;

	Font text;

	Texture background;

	bool l_bt_pressing;
	bool capslock_pressing;

	bool backspace_pressing;

	bool empty;

	bool toggled_CapsLock;
};