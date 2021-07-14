#include "Mouse.h"
#include <SDL_mouse.h>
#include "Key_pressOnce.h"

int Mouse::mX = 0; // obecna pozycja
int Mouse::mY = 0; // obecna pozycja
int Mouse::mX_r = 0; // poprzednia pozycja
int Mouse::mY_r = 0; // poprzednia pozycja

bool Mouse::updated{ false };

bool Mouse::l_pressed_once{ false };

SDL_Point Mouse::clicked_point{};

bool Mouse::keys[100]{};
bool Mouse::pressed_once[100]{};

Key_pressOnce Mouse::lButton_pressOnce{ { Mouse_key::L_BUTTON }};
Key_pressOnce Mouse::rButton_pressOnce{ { Mouse_key::R_BUTTON } };
Key_pressOnce Mouse::midButton_pressOnce{ { Mouse_key::MID_BUTTON }};

Key_pressOnce Mouse::wheelUP_pressOnce{ { Mouse_key::WHEEL_UP} };
Key_pressOnce Mouse::wheelDOWN_pressOnce{ { Mouse_key::WHEEL_DOWN} };

Mouse_key Mouse::key_state{ Mouse_key::NONE };
Mouse_wheel Mouse::wheel_state{ Mouse_wheel::NONE };

void Mouse::update(SDL_Event * ev)
{
	reset_states();

	mY_r = mY;
	mX_r = mX;

	SDL_GetMouseState(&mX, &mY);

	switch (ev->type) {
	case SDL_MOUSEBUTTONDOWN:
		switch_buttons_down(ev);
		break;
	case SDL_MOUSEBUTTONUP:
		updated = true;
		if (ev->button.button == SDL_BUTTON_LEFT)
			keys[int(Mouse_key::L_BUTTON)] = false;
		else if (ev->button.button == SDL_BUTTON_RIGHT)
			keys[int(Mouse_key::R_BUTTON)] = false;
		else if (ev->button.button == SDL_BUTTON_MIDDLE)
			keys[int(Mouse_key::MID_BUTTON)] = false;
		break;
	case SDL_MOUSEWHEEL:
		switch_motion_wheel_FLAG(ev);
		break;
	}

	lButton_pressOnce.events();
	rButton_pressOnce.events();
	midButton_pressOnce.events();
}

bool Mouse::pressedOnce(Mouse_key key)
{
	return pressed_once[int(key)];
}

bool Mouse::pressedOnce(int code)
{
	return pressed_once[code];
}

bool Mouse::is_pressedL_once()
{
	return lButton_pressOnce.pressedOnce();
}

bool Mouse::is_pressedR_once()
{
	return rButton_pressOnce.pressedOnce();
}

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

void Mouse::switch_buttons_down(SDL_Event * ev)
{
	clicked_point = { mX, mY };
	updated = true;

	switch (ev->button.button) {
	case SDL_BUTTON_LEFT:
		key_state = Mouse_key::L_BUTTON;
		l_pressed_once = true;

		keys[int(Mouse_key::L_BUTTON)] = true;
		break;
	case SDL_BUTTON_RIGHT:
		key_state = Mouse_key::R_BUTTON;

		keys[int(Mouse_key::R_BUTTON)] = true;
		break;
	case SDL_BUTTON_MIDDLE:
		key_state = Mouse_key::MID_BUTTON;
		keys[int(Mouse_key::MID_BUTTON)] = true;
		break;
	}
}

void Mouse::reset_states()
{
	key_state = Mouse_key::NONE;
	wheel_state = Mouse_wheel::NONE;

	l_pressed_once = false;

	updated = false;

	keys[int(Mouse_key::WHEEL_UP)] = false;
	keys[int(Mouse_key::WHEEL_DOWN)] = false;
}

void Mouse::switch_motion_wheel_FLAG(SDL_Event * ev)
{
	switch (ev->wheel.direction) {
	case SDL_MOUSEWHEEL_NORMAL:
		if (ev->wheel.y < 0) {
			wheel_state = Mouse_wheel::DOWN;
			keys[int(Mouse_key::WHEEL_DOWN)] = true;
		}
		else {
			wheel_state = Mouse_wheel::UP;
			keys[int(Mouse_key::WHEEL_UP)] = true;
		}

		updated = true;

		break;
	}
}
