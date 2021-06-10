#include "Dynamic_OBJ.h"

Dynamic_OBJ::Dynamic_OBJ(const int & x, const int & y, SDL_RendererFlip flip) :
	Map_OBJ{ x, y }
{
	this->flip = flip;
}

Dynamic_OBJ::Dynamic_OBJ(SDL_Rect mappos, SDL_RendererFlip flip) :
	Map_OBJ{ mappos }
{
	this->flip = flip;
}

void Dynamic_OBJ::events()
{
	Map_OBJ::events();
}

void Dynamic_OBJ::switch_orient()
{
	if (flip == SDL_FLIP_NONE)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_NONE;
}