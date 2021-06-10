#pragma once
#include "Map_OBJ.h"
#include <SDL_render.h>
#include "Texture.h"

struct OBJ_data : MapOBJ_data
{
	SDL_RendererFlip flip;
};

// Dynamic - dynamiczny, poruszaj¹cy siê
class Dynamic_OBJ : public Map_OBJ
{
public:
	Dynamic_OBJ(const int & x, const int & y, Texture * texture, const Size * size, SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		Map_OBJ{ x, y, size }, flip{ Flip }, tX{ texture }
	{}
	Dynamic_OBJ(SDL_Rect mappos, Texture * texture, const Size * size, SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		Map_OBJ{ mappos, size }, flip{ Flip }, tX{ texture }
	{}

	void render();
	void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);
	//virtual void events();

	bool is_flipped() const { return flip != SDL_FLIP_NONE; }

	void switch_orient();

	const Texture & getTX() const { return *tX; }

	virtual ~Dynamic_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	Texture * tX;
	SDL_RendererFlip flip;
};