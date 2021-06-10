#pragma once
#include "Map_OBJ.h"
#include <SDL_render.h>

struct OBJ_data : MapOBJ_data
{
	SDL_RendererFlip flip;
};

// Dynamic - dynamiczny, poruszaj¹cy siê
class Dynamic_OBJ : public Map_OBJ
{
public:
	Dynamic_OBJ(const int & x1, const int & y1, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	virtual void render() = 0;
	virtual void events();

	bool is_flipped() const { return flip != SDL_FLIP_NONE; }

	void switch_orient();

	virtual ~Dynamic_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	SDL_RendererFlip flip;
};