#include "Enemy_OBJ.h"
#include "Mouse.h"

void Enemy_OBJ::events()
{
	Dynamic_OBJ::events();
}

const Enemy_data & Enemy_OBJ::getData()
{
	data.mapX = mapX;
	data.mapY = mapY;
	data.flip = flip;
	data.id = id;

	return data;
}