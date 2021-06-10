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

	void Init(const SDL_Rect & rt);

	const SDL_Rect * getPOS() const { return &position; }

	void update(const std::string & text_to_render);

	void setTEXT(const std::string & text_to_render);
	void setColor(const SDL_Color & cl);

	void setSize(const int & s);

	void loadFont(const std::string & font_path, int size, SDL_Color color);
	void loadFromText(std::string render_text, SDL_Color color);
	//void loadTEXT();


	const int & getHeight() { return Text_TX.getHeight(); }
	const int & getWidth() { return Text_TX.getWidth(); }

	void render(SDL_Renderer * rn, int start, int width, const SDL_Rect * clip = nullptr);

	~Font();
private:
	int Width;
	int Height;

	int textSize;
	SDL_Color textColor;

	SDL_Rect position;

	TTF_Font * font;
	std::string text_to_render;

	Texture Text_TX;
};

