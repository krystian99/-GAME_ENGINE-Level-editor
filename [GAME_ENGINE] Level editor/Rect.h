#pragma once
#include <SDL_rect.h>

struct Rect_Data
{
	SDL_Rect pos;
};

// opakowanie struktury SDL_Rect dla szybszego kodowania
class Rect
{
public:
	Rect(){}
	Rect(Rect&& rect);
	Rect(const Rect& rect);
	Rect(SDL_Rect rect);
	Rect(int x, int y, int w, int h);

	Rect& operator=(Rect&&);
	Rect& operator=(const Rect&);

	void set_position(int x, int y);
	void set_position(int x, int y, int w, int h);
	void set_position(SDL_Rect tmp);

	bool is_inRect(const Rect& rect) const;

	void update_position(int x_udpt, int y_updt);
	void set_scaled_position(SDL_Rect pos);

	int left() const { return pos.x; }
	int right() const { return pos.x + pos.w; }
	int up() const { return pos.y; }
	int down() const { return pos.y + pos.h; }

	void updateX(int upd) { pos.x += upd; }
	void updateY(int upd) { pos.y += upd; }

	void setX(int x) { pos.x = x; }
	void setY(int y) { pos.y = y; }

	int getX() const { return pos.x; }
	int getY() const { return pos.y; }

	const int & getW() const { return pos.w; }
	const int & getH() const { return pos.h; }

	void setW(int w) { pos.w = w; }
	void setH(int h) { pos.h = h; }

	//const SDL_Rect & get() const { return pos; }
	const SDL_Rect& get_position() const { return pos; }

	~Rect() {}
private:
	SDL_Rect pos{};
};

