#include "Map_OBJ.h"
#include "Mouse.h"
#include "Video_Info.h"
#include <cmath>

void Map_OBJ::set_mapPOS(const int & X, const int & Y)
{
	mapX = X;
	mapY = Y;
}
void Map_OBJ::events()
{
	Base_OBJ::events();
}