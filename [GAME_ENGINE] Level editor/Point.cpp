#include "Point.h"

Point::Point(SDL_Point p)
{
	point = p;
}

Point::Point(int x, int y)
{
	set(x, y);
}

void Point::set(int x, int y)
{
	point.x = x;
	point.y = y;
}
