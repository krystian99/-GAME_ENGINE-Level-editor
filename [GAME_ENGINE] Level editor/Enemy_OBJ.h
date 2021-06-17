#pragma once
#include <SDL_render.h>
#include <string>
#include "Enemy_ID.h"
#include "Enemy.h"
#include "Texture.h"
#include <string>
#include "Map_manager.h"
#include <cmath>

// Ka¿dy obiekt bêdzie mia³ ustalon¹ domyœln¹ wartoœæ. Ka¿dy obiekt powinien posiadaæ wartoœæ skalarn¹ dziêki której bêdzie
// mo¿na w czasie dzia³ania programu zmieniaæ wartoœæ. Zmiana wartoœci skalowania bêdzie zmienia³a jednoczeœnie szerokosc
// i wysokoœæ obiektu wzglêdem mapy

template <Enemy_ID id, int w, int h>	// UPDATE: teraz zamiast ustalaæ rozmiar renderowania wzglêdem okna, 
										// bêdzie ustalany wzglêm mapy - w ten sposób wyeleminuje siê kilka niedoci¹gniêæ
										// zwi¹zanych ze skalowaniem i wielokoœci¹ obiektów na ekranach o ró¿nych rozdzielczoœciach.
class Enemy_OBJ : public Enemy {
public:
	static const int W{ w }; // szerokoœæ obiektu wzglêdem mapy - wartoœæ domyœlna, która mo¿e zostaæ przeskalowana
	static const int H{ h }; // wysokoœæ --||--

	Enemy_OBJ(const int & x, const int & y, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);
	Enemy_OBJ(SDL_Rect mappos, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	static Texture & getTexture();

	static void setTexture(const std::string & str);

	static void Init_renderSize();
protected:
	void onMouseOver();
	void onClick();
private:
	static Texture texture;
	static Size size;
};

// zmienne statyczne
template<Enemy_ID id, int w, int h>
Texture Enemy_OBJ<id, w, h>::texture = { };

template<Enemy_ID id, int w, int h>
Size Enemy_OBJ<id, w, h>::size = { w, h };

template<Enemy_ID id, int w, int h>
inline Enemy_OBJ<id, w, h>::Enemy_OBJ(const int & x, const int & y, SDL_RendererFlip flip) :
	Enemy{ x, y, id, &texture, &size, flip } // przekazanie id do interfejsu klasy bazowej
{
	mapPOS.w = std::round(W * SIZE_MULTIPLIER);
	mapPOS.h = std::round(H * SIZE_MULTIPLIER);
}

template<Enemy_ID id, int w, int h>
inline Enemy_OBJ<id, w, h>::Enemy_OBJ(SDL_Rect mappos, SDL_RendererFlip flip) :
	Enemy{ mappos, id, &texture, &size, flip }
{

}

template<Enemy_ID id, int w, int h>
inline void Enemy_OBJ<id, w, h>::setTexture(const std::string & str)
{
	texture.loadFromFile(str);
}

template<Enemy_ID id, int w, int h>
inline void Enemy_OBJ<id, w, h>::Init_renderSize()
{
	double scaleX, scaleY;

	scaleX = double(W) / double(Map_manager::get_mapBG_W());
	scaleY = double(H) / double(Map_manager::get_mapBG_H());

	size.renderW = std::round(Map_manager::get_editW() * scaleX);
	size.renderH = std::round(Map_manager::get_editH() * scaleY);
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
