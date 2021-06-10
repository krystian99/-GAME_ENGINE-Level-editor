#pragma once
#include <SDL_rect.h>
class Point
{
public:
	Point(){}
	Point(SDL_Point p);
	Point(int x, int y);

	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }

	void set(int x, int y);

	int getX() const { return x; }
	int getY() const { return y; }
private:
	int x, y;
};

