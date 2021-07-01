/*#include "Map_OBJ.h"
#include <algorithm>
#include <cmath>

Map_OBJ::Map_OBJ(const int & x, const int & y, const Size * sz) :
	object_size{ sz }
{
	update_mapPOS(x, y);
}

Map_OBJ::Map_OBJ(SDL_Rect map_pos, const Size * sz) :
	object_size{ sz }
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

void Map_OBJ::update_Size()
{
	mapPOS.w = std::round(object_size->mapW * Base_OBJ::SIZE_MULTIPLIER);
	mapPOS.h = std::round(object_size->mapH * Base_OBJ::SIZE_MULTIPLIER);
	render_position.w = std::round(object_size->renderW * Base_OBJ::SIZE_MULTIPLIER);
	render_position.h = std::round(object_size->renderH * Base_OBJ::SIZE_MULTIPLIER);
}*/
