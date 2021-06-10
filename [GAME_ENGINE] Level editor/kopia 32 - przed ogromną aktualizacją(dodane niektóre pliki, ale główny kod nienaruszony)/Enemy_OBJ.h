#pragma once
#include <SDL_render.h>
#include <string>
#include "Dynamic_OBJ.h"
#include "Enemy_ID.h"

struct Enemy_data : public OBJ_data
{
	Enemy_ID id; // Enemy_ID id : 2;musz¹ byæ ustalone pola bitowe, ¿eby dzia³a³o na ka¿dym procesorze
};

class Enemy_OBJ : public Dynamic_OBJ
{
public:
	Enemy_OBJ(const int & x, const int & y, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) :
		Dynamic_OBJ{ x, y, flip }
	{}

	virtual void render() = 0;
	void events();

	const Enemy_ID & getID() const { return id; }

	const Enemy_data & getData();

	virtual ~Enemy_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	Enemy_ID id;
private:
	Enemy_data data;
};