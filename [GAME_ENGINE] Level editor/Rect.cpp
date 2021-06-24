#include "Rect.h"
#include <algorithm>

Rect::Rect(Rect&& rect)
{
	pos = rect.get();
}

Rect::Rect(SDL_Rect r)
{
	pos = r;
}

Rect::Rect(int x, int y, int w, int h)
{
	set(x, y, w, h);
}

void Rect::set(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Rect::set(int x, int y, int w, int h)
{
	pos = { x, y, w, h };
}

void Rect::set(SDL_Rect tmp)
{
	pos = tmp;
}

bool Rect::is_inRect(const Rect& rect) const
{
	return rect.left() > left() && rect.up() > up()
		&& rect.right() < right() && rect.down() < down();
}

void Rect::update(int x, int y)
{
	pos.x += x;
	pos.y += y;
}

Rect & Rect::operator=(Rect&& rect)
{
	set(rect.get());

	return *this;
}
