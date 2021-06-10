#pragma once
#include <string>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "Texture.h"

class Font
{
public:
	Font() {}

	void set_position(const SDL_Rect & rt);

	const SDL_Rect * getPOS() const { return &position; }

	void setTEXT(std::string text_to_render);

	void loadFont(std::string font_path, int height, SDL_Color color);

	const int & getHeight() { return Text_TX.getHeight(); }
	const int & getWidth() { return Text_TX.getWidth(); }

	void render(SDL_Renderer * rn, int start, int width, const SDL_Rect * clip = nullptr);

	~Font();
private:

	int Width;
	int Height;

	SDL_Rect position;

	TTF_Font * font;
	std::string text_to_render;

	Texture Text_TX;
};

