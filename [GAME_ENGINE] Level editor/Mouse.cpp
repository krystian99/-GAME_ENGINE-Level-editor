#include "Mouse.h"
#include <SDL_events.h>
#include <SDL_mouse.h>

int Mouse::mX = 0; // obecna pozycja
int Mouse::mY = 0; // obecna pozycja
int Mouse::mX_r = 0; // poprzednia pozycja
int Mouse::mY_r = 0; // poprzednia pozycja

SDL_Point Mouse::clicked_point{};

bool Mouse::l_pressed{ false };

Mouse_key Mouse::key_state{ Mouse_key::NONE };
Mouse_wheel Mouse::wheel_state{ Mouse_wheel::NONE };

void Mouse::update(SDL_Event * ev)
{
	key_state = Mouse_key::NONE;
	wheel_state = Mouse_wheel::NONE;

	mY_r = mY;
	mX_r = mX;

	SDL_GetMouseState(&mX, &mY);

	switch (ev->type) {
	case SDL_MOUSEBUTTONDOWN:
		switch_buttons_down(ev);
		break;
	case SDL_MOUSEBUTTONUP:
		if (ev->button.button == SDL_BUTTON_LEFT)
			l_pressed = false;
		break;
	case SDL_MOUSEWHEEL:
		switch_motion_wheel_FLAG(ev);
		break;
	}
}

/*const bool & Mouse::check_clickedPoint(const SDL_Rect & pos)
{
	if (clicked_point.x >= pos.x && clicked_point.x <= pos.x + pos.w
		&& clicked_point.y >= pos.y && clicked_point.y <= pos.y + pos.h)
	{
		return true;
	}
	return false;
}*/

bool Mouse::is_inPOS(const SDL_Rect & pos)
{
	if (Mouse::getX() >= pos.x && Mouse::getX() <= pos.x + pos.w
		&& Mouse::getY() >= pos.y && Mouse::getY() <= pos.y + pos.h)
		return true;
	return false;
}

bool Mouse::clickedPoint_inPOS(const Rect& pos)
{
	if (clicked_point.x >= pos.left() && clicked_point.x <= pos.right()
		&& clicked_point.y >= pos.up() && clicked_point.y <= pos.down())
		return true;

	return false;
}

bool Mouse::moved()
{
	return mX != mX_r || mY != mY_r;
}

void Mouse::switch_buttons_down(SDL_Event * ev)
{
	switch (ev->button.button) {
	case SDL_BUTTON_LEFT:
		key_state = Mouse_key::L_BUTTON;
		clicked_point = { mX, mY };
		l_pressed = true;
		break;
	case SDL_BUTTON_RIGHT:
		key_state = Mouse_key::R_BUTTON;
		clicked_point = { mX, mY };
		break;
	case SDL_BUTTON_MIDDLE:
		key_state = Mouse_key::MID_BUTTON;
		break;
	}
}

void Mouse::switch_motion_wheel_FLAG(SDL_Event * ev)
{
	switch (ev->wheel.direction) {
	case SDL_MOUSEWHEEL_NORMAL:
		if (ev->wheel.y < 0)
			wheel_state = Mouse_wheel::DOWN;
		else
			wheel_state = Mouse_wheel::UP;
		break;
	}
}