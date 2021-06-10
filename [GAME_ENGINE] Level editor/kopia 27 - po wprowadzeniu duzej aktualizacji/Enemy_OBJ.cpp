#include "Enemy_OBJ.h"
#include "Mouse.h"

Enemy_OBJ::Enemy_OBJ(const int & x1, const int & y1)
	: x{ x1 }, y{ y1 }
{
	render_position.w = w;
	render_position.h = h;

	data = { x, y };
};

void Enemy_OBJ::setPOS(const SDL_Rect & rt)
{
	x = rt.x;
	y = rt.y;
}

void Enemy_OBJ::set_mapPOS(const int & X, const int & Y)
{
	x = X;
	y = Y;

	data.map_x = X;
	data.map_y = Y;
}

void Enemy_OBJ::setRenderPos(const int & render_X, const int & render_Y)
{
	render_position.x = render_X;
	render_position.y = render_Y;
}

void Enemy_OBJ::events()
{
	mouse_handler();
}

void Enemy_OBJ::mouse_handler()
{
	int mX = Mouse::getX();
	int mY = Mouse::getY();

	clicked = false;

	if (mX >= render_position.x && mX <= render_position.x + render_position.w
		&& mY >= render_position.y && mY <= render_position.y + render_position.h)
	{
		if (Mouse::getBt_state() == Mouse_key::L_BUTTON && !clicked)
			clicked = true;
		else if (Mouse::getBt_state() == Mouse_key::NONE)
			clicked = false;
	}
}

void Enemy_OBJ::setTexture(const std::string & bg)
{
	TX.loadFromFile(bg);
}

void Enemy_OBJ::render()
{
	TX.render(nullptr, &render_position);
}