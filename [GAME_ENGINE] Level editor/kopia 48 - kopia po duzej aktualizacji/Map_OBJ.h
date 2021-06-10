#pragma once
#include <SDL_rect.h>
#include "Base_OBJ.h"

struct Size {
	int mapW, mapH; // --||--
	int renderW, renderH; // ka¿dy obiekt egzemlarzu klasy szablonowej posiada jedn¹ kopiê wspó³dzielon¹ ze wszystkimi obiektami
};

struct MapOBJ_data {
	SDL_Rect mapPOS;
};

class Map_OBJ : public Base_OBJ
{
public:
	Map_OBJ(const int & x, const int & y, const Size * sz);
	Map_OBJ(SDL_Rect map_pos, const Size * sz);

	void update_mapPOS(const int & X, const int & Y);

	void events();

	void update_Size();

	const SDL_Rect & get_mapPOS() const { return mapPOS; }

	const int & get_mapX() const { return mapPOS.x; }
	const int & get_mapY() const { return mapPOS.y; }

	virtual ~Map_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	SDL_Rect mapPOS;
private:
	const Size * object_size;
};