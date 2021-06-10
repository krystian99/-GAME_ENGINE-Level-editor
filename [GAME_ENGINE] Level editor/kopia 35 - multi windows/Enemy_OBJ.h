#pragma once
#include <SDL_render.h>
#include <string>
#include "Enemy_ID.h"
#include "Enemy.h"
#include "Texture.h"
#include <string>

template <Enemy_ID id, int w, int h>
class Enemy_OBJ : public Enemy {
public:
	static const int W{ w };
	static const int H{ h };

	Enemy_OBJ(const int & x, const int & y, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	static Texture & getTexture();

	static void setTexture(const std::string & str);
protected:
	void onMouseOver();
	void onClick();
private:
	static Texture texture;
};

template<Enemy_ID id, int w, int h> // zmienna statyczna
Texture Enemy_OBJ<id, w, h>::texture = { };

template<Enemy_ID id, int w, int h>
inline Enemy_OBJ<id, w, h>::Enemy_OBJ(const int & x, const int & y, SDL_RendererFlip flip) :
	Enemy{ x, y, id, &texture, flip } // przekazanie id do interfejsu klasy bazowej
{
	render_position.w = W;
	render_position.h = H;
}

template<Enemy_ID id, int w, int h>
inline void Enemy_OBJ<id, w, h>::setTexture(const std::string & str)
{
	texture.loadFromFile(str);
}

template<Enemy_ID id, int w, int h>
inline Texture & Enemy_OBJ<id, w, h>::getTexture()
{
	return texture;
}

template<Enemy_ID id, int w, int h>
inline void Enemy_OBJ<id, w, h>::onMouseOver()
{

}

template<Enemy_ID id, int w, int h>
inline void Enemy_OBJ<id, w, h>::onClick()
{

}