#pragma once
#include <SDL_rect.h>

class Point
{
public:
	Point(){}
	Point(SDL_Point p);
	Point(int x, int y);

	void setX(int x) { this->point.x = x; }
	void setY(int y) { this->point.y = y; }

	void set(int x, int y);

	const SDL_Point& get() const { return point; }

	int getX() const { return point.x; }
	int getY() const { return point.y; }
private:
	SDL_Point point{};
	//int x{}, y{};
};

