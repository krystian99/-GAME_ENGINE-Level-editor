#pragma once
#include <SDL_rect.h>
#include "Base_OBJ.h"

struct MapOBJ_data {
	int mapX, mapY;
};

class Map_OBJ : public Base_OBJ
{
public:
	Map_OBJ(const int & x, const int & y) :
		mapX{ x }, mapY{ y }
	{}

	void set_mapPOS(const int & X, const int & Y);

	virtual void render() = 0;
	virtual void events();

	// aktualizuje i przekazuje dane
	//virtual const MapOBJ_data & getData() = 0;

	const int & get_mapX() const { return mapX; }
	const int & get_mapY() const { return mapY; }

	virtual ~Map_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	int mapX, mapY;
};