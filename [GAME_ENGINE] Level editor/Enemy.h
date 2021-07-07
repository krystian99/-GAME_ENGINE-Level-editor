#pragma once
#include <SDL_render.h>
#include "Dynamic_OBJ.h"
#include "Enemy_ID.h"
#include "Texture.h"
#include <memory>

class Enemy;

using Enemy_ptr = std::shared_ptr<Enemy>;

struct Enemy_data : public OBJ_data
{
	Enemy_ID id; 
};

class Enemy : public Dynamic_OBJ
{
public:
	Enemy(const int & x, const int & y, Enemy_ID ID, Texture * tx, const Size * size, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		Dynamic_OBJ{ x, y, tx, size, flip }, id_enemy{ ID }//, tX{ tx }
	{}

	Enemy(SDL_Rect map_pos, Enemy_ID ID, Texture * tx, const Size * size, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		Dynamic_OBJ{ map_pos, tx, size, flip }, id_enemy{ ID }//, tX{ tx }
	{}

	const Enemy_ID & getID() const { return id_enemy; }
	const Enemy_data & getData();

	virtual ~Enemy() {}
protected:
	virtual void on_mouseOver();
	virtual void on_mouseOut();

	//virtual void onClick() = 0;
private:
	Enemy_ID id_enemy;
	Enemy_data data;
};