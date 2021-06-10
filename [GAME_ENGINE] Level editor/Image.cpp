#include "Image.h"
#include "Video_Info.h"

Image::Image(SDL_Rect pos, const char * tX)
{
	texture.loadFromFile(tX);
	position = pos;
	Video_Info::set_scaledSize(position);
}

void Image::render()
{
	texture.render(nullptr, &position);
}