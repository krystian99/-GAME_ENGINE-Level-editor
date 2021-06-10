#pragma once
#include <SDL_render.h>
#include <string>
#include "Enemy_ID.h"
#include "Enemy.h"
#include "Texture.h"
#include <string>
#include "Map_EditArea_manager.h"

// Ka¿dy obiekt bêdzie mia³ ustalon¹ domyœln¹ wartoœæ. Ka¿dy obiekt powinien posiadaæ wartoœæ skalarn¹ dziêki której bêdzie
// mo¿na w czasie dzia³ania programu zmieniaæ wartoœæ. Zmiana wartoœci skalowania bêdzie zmienia³a jednoczeœnie szerokosc
// i wysokoœæ obiektu wzglêdem mapy

template <Enemy_ID id, int w, int h>	// UPDATE: teraz zamiast ustalaæ rozmiar renderowania wzglêdem okna, 
										// bêdzie ustalany wzglêm mapy - w ten sposób wyeleminuje siê kilka niedoci¹gniêæ
										// zwi¹zanych ze skalowaniem i wielokoœci¹ obiektów na ekranach o ró¿nych rozdzielczoœciach.
class Enemy_OBJ : public Enemy {
public:
	static const int W{ w }; // szerokoœæ obiektu wzglêdem mapy
	static const int H{ h }; // wysokoœæ --||--

	Enemy_OBJ(const int & x, const int & y, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

	static Texture & getTexture();

	//static int get_renderW();
	//static int get_renderH();

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
	//render_position.w = W;
	//render_position.h = H;

	mapPOS.w = W;
	mapPOS.h = H;
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

/*template<Enemy_ID id, int w, int h>
inline int Enemy_OBJ<id, w, h>::get_renderW()
{
	static double scaleX;

	scaleX = double(mapPOS.x + mapPOS.w) / double(Map_EditArea_manager::get_mapBG_W());

	return round(scaleX * Map_EditArea_manager::get_editW());
}

template<Enemy_ID id, int w, int h>
inline int Enemy_OBJ<id, w, h>::get_renderH()
{
	static double scaleY;

	scaleY = double(mapPOS.y + mapPOS.h) / double(Map_EditArea_manager::get_mapBG_H());

	return round(scaleY * Map_EditArea_manager::get_editH());
}*/

template<Enemy_ID id, int w, int h>
inline void Enemy_OBJ<id, w, h>::onMouseOver()
{

}

template<Enemy_ID id, int w, int h>
inline void Enemy_OBJ<id, w, h>::onClick()
{

}