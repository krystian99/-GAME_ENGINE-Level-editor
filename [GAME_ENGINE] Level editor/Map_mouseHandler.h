#pragma once
#include "Point.h"

class Map_mouseHandler
{
public:
	Map_mouseHandler(){}

	void events(bool mouse_over);

	int getX_point() const { return clicked_point.getX(); }
	int getY_point() const { return clicked_point.getY(); }

	const Point& get_clickedPoint() const { return clicked_point; }
private:
	Point clicked_point;
};