#pragma once
#include "MapOBJ.h"
#include <SDL_render.h>
#include "Texture.h"

struct Dynamic_OBJ_data : MapOBJ_data
{
	SDL_RendererFlip flip;
};

// Dynamic - dynamiczny, poruszaj¹cy siê
class Dynamic_OBJ : public MapOBJ
{
public:
	Dynamic_OBJ(const int & x, const int & y, Texture * texture, const Size * size, SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		MapOBJ{ x, y, size, texture }, flip{ Flip }, tX{ texture }
	{}
	Dynamic_OBJ(SDL_Rect mappos, Texture * texture, const Size * size, SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		MapOBJ{ mappos, size, texture }, flip{ Flip }, tX{ texture }
	{}

	void render();
	void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);

	bool is_flipped() const { return flip != SDL_FLIP_NONE; }

	void switch_orient();

	const Texture & getTX() const { return *tX; }

	virtual ~Dynamic_OBJ() {}
protected:
	virtual void on_mouseOver();
	virtual void on_mouseOut();

	virtual void onClick(){}
protected:
	Texture * tX;
	SDL_RendererFlip flip;
};