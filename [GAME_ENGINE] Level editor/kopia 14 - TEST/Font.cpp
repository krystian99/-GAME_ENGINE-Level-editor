#include "Font.h"
#include "Setup.h"
#include "Exceptions.h"

void Font::set_position(const SDL_Rect & rt)
{
	position = rt;
	Width = rt.w;
	Height = rt.h;
}

void Font::Init(const SDL_Rect & rt)
{
	position = rt;
	Width = rt.w;
	Height = rt.h;
}

void Font::update(const std::string & text_to_render)
{
	Text_TX.loadFromText(text_to_render, font, textColor);
}

void Font::setTEXT(const std::string & text_to_rn)
{
	text_to_render = text_to_rn;
}

void Font::setColor(const SDL_Color & cl)
{
	textColor = cl;
}

void Font::setSize(const int & size)
{
	textSize = size;
}

void Font::loadFont(const std::string & font_path, int size, SDL_Color color)
{
	textSize = size;
	textColor = color;

	if (!(font = TTF_OpenFont(font_path.c_str(), size))) // ³aduje text 
		throw Error{ "Cannot load true type font!: " + std::string{ SDL_GetError() } };

	Text_TX.loadFromText(text_to_render, font, color);
}


void Font::render(SDL_Renderer * rn, int start, int width, const SDL_Rect * clip) // clip - obszar do renderowania
{
	if (clip) {
		SDL_Rect part_of_text = { start, 0, width, Text_TX.getHeight() };
		Text_TX.render(rn, &part_of_text, clip);
	}
	else
		Text_TX.render(rn, nullptr, &position);
}

Font::~Font()
{
	if (!font)
		TTF_CloseFont(font);
}
