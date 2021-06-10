#include "Dynamic_OBJ.h"

Dynamic_OBJ::Dynamic_OBJ(const int & x, const int & y, SDL_RendererFlip flip) :
	Map_OBJ{ x, y }
{
	this->flip = flip;
}

void Dynamic_OBJ::events()
{
	Map_OBJ::events();
}