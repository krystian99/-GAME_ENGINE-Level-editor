#include "Map_OBJ.h"

Map_OBJ::Map_OBJ(const int & x, const int & y)
{
	update_mapPOS(x, y);
}

Map_OBJ::Map_OBJ(SDL_Rect map_pos)
{
	mapPOS = map_pos;
}

void Map_OBJ::update_mapPOS(const int & X, const int & Y)
{
	mapPOS.x = X;
	mapPOS.y = Y;
}

void Map_OBJ::events()
{
	Base_OBJ::events();
}