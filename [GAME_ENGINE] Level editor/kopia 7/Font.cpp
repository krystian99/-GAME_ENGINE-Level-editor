#include "Font.h"
#include "Setup.h"
#include "Exceptions.h"

void Font::set_position(const SDL_Rect & rt)
{
	position = rt;
	Width = rt.w;
	Height = rt.h;
}

void Font::setTEXT(std::string text_to_rn)
{
	text_to_render = text_to_rn;
}

void Font::loadFont(std::string font_path, int height, SDL_Color color)
{
	if (!(font = TTF_OpenFont(font_path.c_str(), height))) // ³aduje text 
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
