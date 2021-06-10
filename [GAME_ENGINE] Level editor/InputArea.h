#pragma once
#include <string>
#include <SDL_render.h>
#include "Text.h"
#include "Texture.h"
#include <SDL_keyboard.h>

class InputArea
{
public:
	InputArea(const SDL_Rect & pos, const int & startX, const int & startY, const std::string & font_path, int size_text, const SDL_Color & color_text, bool Digit_enabled = true, bool Alpha_enabled = true);
	InputArea(SDL_Renderer * rn, const SDL_Rect & pos, const int & startX, const int & startY, const std::string & font_path, int size_text, const SDL_Color & color_text, bool Digit_enabled = true, bool Alpha_enabled = true);

	void render();
	void render(SDL_Renderer * rn);
	void events();

	void load_background(const std::string & d);

	const std::string & getStr() const { return input; }

	bool is_clicked() const { return clicked; }

	void reset();

	const bool & is_empty() const { return empty; }

	void setCurrent(bool x);
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

	const Uint8 * keyboard{ nullptr };

	Text text;

	SDL_Renderer * rn{ nullptr };

	Texture background;

	bool digits_enabled, alpha_enabled;

	bool backspace_pressing{ false };

	bool empty{ true };

	bool clicked{ false };

	bool current{ false };
};