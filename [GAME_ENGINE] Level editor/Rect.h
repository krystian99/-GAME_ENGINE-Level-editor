#pragma once
#include <SDL_rect.h>

// opakowanie struktury SDL_Rect dla szybszego kodowania
class Rect
{
public:
	Rect(){}
	Rect(Rect&& rect);
	Rect(SDL_Rect rect);
	Rect(int x, int y, int w, int h);

	Rect& operator=(Rect&&);

	void set(int x, int y);
	void set(int x, int y, int w, int h);
	void set(SDL_Rect tmp);

	void update(int x, int y);

	int left() const { return pos.x; }
	int right() const { return pos.x + pos.w; }
	int up() const { return pos.y; }
	int down() const { return pos.y + pos.h; }

	void updateX(int upd) { pos.x += upd; }
	void updateY(int upd) { pos.y += upd; }

	void setX(int x) { pos.x = x; }
	void setY(int y) { pos.y = y; }

	const int & getW() const { return pos.w; }
	const int & getH() const { return pos.h; }

	void setW(int w) { pos.w = w; }
	void setH(int h) { pos.h = h; }

	const SDL_Rect & get() const { return pos; }

	~Rect() {}
private:
	SDL_Rect pos{};
};

