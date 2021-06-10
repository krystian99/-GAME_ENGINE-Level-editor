#include "Dynamic_OBJ.h"

void Dynamic_OBJ::render()
{
	tX->render(nullptr, &render_position, flip);
}

void Dynamic_OBJ::render(const SDL_Rect & tX_area, const SDL_Rect & destination_area)
{
	tX->render(&tX_area, &destination_area, flip);
}

/*void Dynamic_OBJ::events()
{
	Map_OBJ::events();
}*/

void Dynamic_OBJ::switch_orient()
{
	if (flip == SDL_FLIP_NONE)
		flip = SDL_FLIP_HORIZONTAL;
	else
		flip = SDL_FLIP_NONE;
}