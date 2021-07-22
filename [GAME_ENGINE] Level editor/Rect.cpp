#include "Rect.h"
#include <algorithm>
#include "Video_Info.h"

Rect::Rect(Rect&& rect)
{
	pos = rect.get_position();
}

Rect::Rect(const Rect& rect)
{
	pos = rect.get_position();
}

Rect::Rect(SDL_Rect r)
{
	pos = r;
}

Rect::Rect(int x, int y, int w, int h)
{
	set_position(x, y, w, h);
}

void Rect::set_position(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Rect::set_position(int x, int y, int w, int h)
{
	pos = { x, y, w, h };
}

void Rect::set_position(SDL_Rect tmp)
{
	pos = tmp;
}

bool Rect::is_inRect(const Rect& rect) const
{
	return rect.left() > left() && rect.up() > up()
		&& rect.right() < right() && rect.down() < down();
}

void Rect::set_scaled_position(SDL_Rect position)
{
	pos = position;
	Video_Info::set_scaledSize(pos);
}

void Rect::update_position(int x, int y)
{
	pos.x += x;
	pos.y += y;
}

Rect & Rect::operator=(Rect&& rect)
{
	set_position(rect.get_position());

	return *this;
}

Rect& Rect::operator=(const Rect& rect)
{
	pos = rect.get_position();
	/*pos.x = rect.left();
	pos.y = rect.up();
	pos.w = rect.getW();
	pos.h = rect.getH();*/

	return *this;
}
