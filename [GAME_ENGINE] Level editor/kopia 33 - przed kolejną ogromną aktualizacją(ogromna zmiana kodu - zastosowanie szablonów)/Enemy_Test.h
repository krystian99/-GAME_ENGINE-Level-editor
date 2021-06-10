#pragma once
#include "Enemy_OBJ.h"
#include "Texture.h"

class Enemy_Test final : public Enemy_OBJ // w takim obiekcie pochodnym ustalane s¹ tylko jego wymiary, textura i zawartosc ekwipunku
{
public:
	Enemy_Test(const int & x, const int & y, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	// stale wymiary
	static const int width = 30;
	// stale wymiary
	static const int height = 50;

	static Texture & getTexture() { return tX; }

	void render();
	static void setTexture(const std::string & bg);

	~Enemy_Test() {}
private:
	void onMouseOver();
	void onClick();
private:
	static Texture tX; // textura dla wszystkich obiektów tego typu
};