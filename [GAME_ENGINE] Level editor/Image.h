#pragma once
#include "Texture.h"
#include <SDL_rect.h>

class Image // zwyk³a textura z po³o¿eniem SDL_Rect pos;
{
public:
	Image(SDL_Rect pos, const char * tX);

	void render();
private:
	SDL_Rect position;

	Texture texture;
};