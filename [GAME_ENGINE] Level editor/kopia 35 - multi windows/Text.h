#pragma once
#include <string>
#include <SDL_render.h>
#include "Texture.h"

struct _TTF_Font;

class Text
{
public:
	Text(const int & startX, const int & startY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text);
	Text(const int & startX, const int & startY, const std::string & font_path, int size_text, const SDL_Color & color_text);

	void loadFromText(std::string render_text, SDL_Color color);

	void update(const std::string & text_to_render);

	const int & getHeight() { return Text_TX.getHeight(); }
	const int & getWidth() { return Text_TX.getWidth(); }

	void setPOS(const SDL_Rect & rt);

	const SDL_Rect * getPOS() const { return &position; }

	void render(int start, int width, const SDL_Rect * clip = nullptr);
	void render(SDL_Renderer * rn, int start, int width, const SDL_Rect * clip = nullptr);
	void render();
private:
	void loadFont(const std::string & font_path, int size, SDL_Color color);
private:
	int Width;
	int Height;

	int textSize;
	SDL_Color textColor;

	SDL_Rect position;

	_TTF_Font * font;
	std::string text_to_render;

	Texture Text_TX;
};