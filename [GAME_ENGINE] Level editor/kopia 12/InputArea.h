#pragma once
#include <string>
#include <SDL_render.h>
#include <cctype>
#include "Font.h"
#include "Texture.h"

//enum class InputArea_state { SELECTED, UNSELECTED };

class InputArea
{
public:
	InputArea() :
		toggled_CapsLock{ false },
		//state{ InputArea_state::UNSELECTED },
		l_bt_pressing{ false },
		capslock_pressing{ false },
		backspace_pressing{ false }
	{}

	void Init(const SDL_Rect & rt, const int & size, const SDL_Color & color);

	void get();

	void events(SDL_Renderer * rn);

	void loadTX(std::string d) { background.loadFromFile(d); }

	void set_TextSize(const int & size);
	void set_TextColor(const SDL_Color & color);

	//const InputArea_state & getState() const { return state; }

	~InputArea() {}
private:
	void addBack(char && c);

	void updateTEXT();

	void getLiters();
	void getOthers();

	void mouse_handler();
private:
	std::string input;

	//InputArea_state state;

	SDL_Rect position;
	SDL_Rect textPOS;

	Font text;

	Texture background;

	bool l_bt_pressing;
	bool capslock_pressing;

	bool backspace_pressing;

	bool toggled_CapsLock;
};