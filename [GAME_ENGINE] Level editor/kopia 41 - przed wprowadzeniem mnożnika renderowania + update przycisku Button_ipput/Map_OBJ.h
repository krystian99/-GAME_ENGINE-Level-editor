#pragma once
#include <SDL_rect.h>
#include "Base_OBJ.h"

struct MapOBJ_data {
	SDL_Rect mapPOS;
};

class Map_OBJ : public Base_OBJ
{
public:
	Map_OBJ(const int & x, const int & y);
	Map_OBJ(SDL_Rect map_pos);

	void update_mapPOS(const int & X, const int & Y);

	virtual void render() = 0;
	virtual void events();

	const SDL_Rect & get_mapPOS() const { return mapPOS; }

	const int & get_mapX() const { return mapPOS.x; }
	const int & get_mapY() const { return mapPOS.y; }

	virtual ~Map_OBJ() {}
protected:
	virtual void onMouseOver() = 0;
	virtual void onClick() = 0;
protected:
	SDL_Rect mapPOS;
};