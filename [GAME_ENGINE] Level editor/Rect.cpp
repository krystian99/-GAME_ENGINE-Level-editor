#include "Rect.h"

Rect::Rect(SDL_Rect r)
{
	pos.x = r.x;
	pos.y = r.y;
	pos.w = r.w;
	pos.h = r.h;
}

Rect::Rect(int x, int y, int w, int h)
{
	set(x, y, w, h);
}

void Rect::set(int x, int y, int w, int h)
{
	pos = { x, y, w, h };
}

void Rect::set(SDL_Rect tmp)
{
	pos = tmp;
}

void Rect::update(int x, int y)
{
	pos.x += x;
	pos.y += y;
}
