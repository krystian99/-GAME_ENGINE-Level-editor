#include "Text.h"
#include "Error.h"
#include <SDL_ttf.h>
#include "Video_Info.h"

Text::Text(const int & startX, const int & startY, const std::string & font_path, const std::string & render_text, int size_text, const SDL_Color & color_text) :
	Text{ startX, startY, font_path, size_text, color_text }
{
	Text_TX.loadFromText(render_text, font, color_text);

	position.w = Text_TX.getWidth();
	position.h = Text_TX.getHeight();
}

Text::Text(const int & startX, const int & startY, const std::string & font_path, int size_text, const SDL_Color & color_text)
{
	loadFont(font_path, size_text, color_text);
	int X = std::round(startX * Video_Info::get_scaleW());
	int Y = std::round(startY * Video_Info::get_scaleH());

	position = { X, Y };
}

void Text::loadFont(const std::string & font_path, int size, SDL_Color color)
{
	textSize = std::round(size * Video_Info::get_scaleH());
	textColor = color;

	if (!(font = TTF_OpenFont(font_path.c_str(), textSize))) // ³aduje text 
		throw Error::throw_Message("Cannot load true type font!: " + std::string{ SDL_GetError() });
}

void Text::loadFromText(std::string render_text, SDL_Color color)
{
	Text_TX.loadFromText(text_to_render, font, color);
}

void Text::update(const std::string & text_to_render)
{
	Text_TX.loadFromText(text_to_render, font, textColor);
	position.w = Text_TX.getWidth();
	position.h = Text_TX.getHeight();
}

void Text::update(SDL_Renderer * rn, const std::string & text_to_render)
{
	Text_TX.loadFromText(rn, text_to_render, font, textColor);
	position.w = Text_TX.getWidth();
	position.h = Text_TX.getHeight();
}

void Text::setPOS(const SDL_Rect & rt)
{
	position = rt;
}

void Text::render(int start, int width, const SDL_Rect * clip) // clip - obszar do renderowania
{
	if (Text_TX.is_loaded()) {
		if (clip) {
			SDL_Rect part_of_text = { start, 0, width, Text_TX.getHeight() };
			Text_TX.render(&part_of_text, clip);
		}
		else
			Text_TX.render(nullptr, &position);
	}
}

void Text::render(SDL_Renderer * rn, int start, int width, const SDL_Rect * clip)
{
	if (Text_TX.is_loaded()) {
		if (clip) {
			SDL_Rect part_of_text = { start, 0, width, Text_TX.getHeight() };
			Text_TX.render(rn, &part_of_text, clip);
		}
		else
			Text_TX.render(rn, nullptr, &position);
	}
}

void Text::render()
{
	if (Text_TX.is_loaded())
		Text_TX.render(nullptr, &position);
}