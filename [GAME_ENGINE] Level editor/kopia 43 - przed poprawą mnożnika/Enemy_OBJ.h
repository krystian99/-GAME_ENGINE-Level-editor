#pragma once
#include <SDL_render.h>
#include <string>
#include "Enemy_ID.h"
#include "Enemy.h"
#include "Texture.h"
#include <string>
#include "Map_EditArea_manager.h"

// Ka�dy obiekt b�dzie mia� ustalon� domy�ln� warto��. Ka�dy obiekt powinien posiada� warto�� skalarn� dzi�ki kt�rej b�dzie
// mo�na w czasie dzia�ania programu zmienia� warto��. Zmiana warto�ci skalowania b�dzie zmienia�a jednocze�nie szerokosc
// i wysoko�� obiektu wzgl�dem mapy

template <Enemy_ID id, int w, int h>	// UPDATE: teraz zamiast ustala� rozmiar renderowania wzgl�dem okna, 
										// b�dzie ustalany wzgl�m mapy - w ten spos�b wyeleminuje si� kilka niedoci�gni��
										// zwi�zanych ze skalowaniem i wieloko�ci� obiekt�w na ekranach o r�nych rozdzielczo�ciach.
class Enemy_OBJ : public Enemy {
public:
	static int W; // szeroko�� obiektu wzgl�dem mapy
	static int H; // wysoko�� --||--

	static const int & getW() { return W; }
	static const int & getH() { return H; }

	Enemy_OBJ(const int & x, const int & y, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);
	Enemy_OBJ(SDL_Rect mappos, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

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

template<Enemy_ID id, int w, int h> // zmienna statyczna
int Enemy_OBJ<id, w, h>::W = { w };

template<Enemy_ID id, int w, int h> // zmienna statyczna
int Enemy_OBJ<id, w, h>::H = { h };

template<Enemy_ID id, int w, int h>
inline Enemy_OBJ<id, w, h>::Enemy_OBJ(const int & x, const int & y, SDL_RendererFlip flip) :
	Enemy{ x, y, id, &texture, flip } // przekazanie id do interfejsu klasy bazowej
{
	mapPOS.w = W;
	mapPOS.h = H;
}

template<Enemy_ID id, int w, int h>
inline Enemy_OBJ<id, w, h>::Enemy_OBJ(SDL_Rect mappos, SDL_RendererFlip flip) :
	Enemy{ mappos, id, &texture, flip }
{

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