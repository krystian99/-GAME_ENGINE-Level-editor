#pragma once
#include <SDL_rect.h>
#include "Base_OBJ.h"

struct MapOBJ_data {
	int mapX, mapY;
	SDL_Rect mapPOS;
};

class Map_OBJ : public Base_OBJ
{
public:
	Map_OBJ(const int & x, const int & y) : // zostawione dla testow
		mapX{ x }, mapY{ y }
	{}
	//Map_OBJ(const int & x, const int & y);

	void set_mapPOS(const int & X, const int & Y);

	virtual void render() = 0;
	virtual void events();

	const SDL_Rect & get_mapPOS() const { return mapPOS; }

	const int & get_mapX() const { return mapX; }
	const int & get_mapY() const { return mapY; }

	virtual ~Map_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	int mapX, mapY;
	SDL_Rect mapPOS;
};