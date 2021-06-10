#pragma once
#include "Enemy_OBJ.h"
#include <SDL_render.h>
#include "Texture.h"

class Enemy_TEST2 : public Enemy_OBJ
{
public:
	Enemy_TEST2(const int & x, const int & y, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	// stale wymiary
	static const int width = 30;
	// stale wymiary
	static const int height = 50;

	static Texture & getTexture() { return tX; }

	void render();
	static void setTexture(const std::string & bg);
private:
	void onMouseOver();
	void onClick();
private:
	static Texture tX; // textura dla wszystkich obiektów tego typu
};