#include "Point.h"

Point::Point(SDL_Point p)
{
	x = p.x;
	y = p.y;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Point::set(int x, int y)
{
	this->x = x;
	this->y = y;
}
