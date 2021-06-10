#pragma once
#include <SDL_render.h>
#include "Dynamic_OBJ.h"
#include "Enemy_ID.h"
#include "Texture.h"

struct Enemy_data : public OBJ_data
{
	Enemy_ID id; 
};

class Enemy : public Dynamic_OBJ
{
public:
	Enemy(const int & x, const int & y, Enemy_ID ID, Texture * tx, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		Dynamic_OBJ{ x, y, flip }, id_enemy{ ID }, tX{ tx }
	{}

	Enemy(SDL_Rect map_pos, Enemy_ID ID, Texture * tx, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		Dynamic_OBJ{ map_pos, flip }, id_enemy{ ID }, tX{ tx }
	{}

	void render(); // funkcje render i events bêd¹ znajdowa³y siê w przysz³oœci tylko w klasie Dynamic_OBJ
	void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);
	void events();

	const Texture & getTX() const;

	const Enemy_ID & getID() const { return id_enemy; }
	const Enemy_data & getData();

	virtual ~Enemy() {}
protected:
	virtual void onMouseOver() = 0;
	void onClick();
private:
	Texture * tX;
	Enemy_ID id_enemy;
	Enemy_data data;
};