#include "Mouse.h"
#include <SDL_mouse.h>
#include "Key_pressOnce.h"

int Mouse::mX = 0; // obecna pozycja
int Mouse::mY = 0; // obecna pozycja
int Mouse::mX_r = 0; // poprzednia pozycja
int Mouse::mY_r = 0; // poprzednia pozycja

bool Mouse::updated{ false };

SDL_Point Mouse::clicked_point{};

bool Mouse::keys[1000]{};

Key_pressOnce Mouse::lButton_pressOnce{ { Mouse_key::L_BUTTON }};
Key_pressOnce Mouse::rButton_pressOnce{ { Mouse_key::R_BUTTON } };
Key_pressOnce Mouse::midButton_pressOnce{ { Mouse_key::MID_BUTTON }};

Mouse_key Mouse::key_state{ Mouse_key::NONE };
Mouse_wheel Mouse::wheel_state{ Mouse_wheel::NONE };

void Mouse::update(SDL_Event * ev)
{
	key_state = Mouse_key::NONE;
	wheel_state = Mouse_wheel::NONE;

	mY_r = mY;
	mX_r = mX;

	lButton_pressOnce.events();
	rButton_pressOnce.events();
	midButton_pressOnce.events();

	SDL_GetMouseState(&mX, &mY);

	switch (ev->type) {
	case SDL_MOUSEBUTTONDOWN:
		switch_buttons_down(ev);
		break;
	case SDL_MOUSEBUTTONUP:
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
	default:
		updated = false;
		break;
	}
}

bool Mouse::pressedOnce(Mouse_key key)
{
	switch (key)
	{
	case Mouse_key::L_BUTTON:
		return lButton_pressOnce.pressedOnce();
		break;
	case Mouse_key::R_BUTTON:
		return rButton_pressOnce.pressedOnce();
		break;
	case Mouse_key::MID_BUTTON:
		return midButton_pressOnce.pressedOnce();
		break;
	}
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
		keys[int(Mouse_key::L_BUTTON)] = true;
		updated = true;
		break;
	case SDL_BUTTON_RIGHT:
		key_state = Mouse_key::R_BUTTON;
		clicked_point = { mX, mY };
		keys[int(Mouse_key::R_BUTTON)] = true;
		updated = true;
		break;
	case SDL_BUTTON_MIDDLE:
		key_state = Mouse_key::MID_BUTTON;
		keys[int(Mouse_key::MID_BUTTON)] = true;
		updated = true;
		break;
	default:
		updated = false;
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

		updated = true;

		break;
	}
}

/*Mouse::Key_pressOnce::Key_pressOnce(const std::vector<Mouse_key>& keys, const bool * mouse_ks) :
	mouse_keys{ mouse_ks }
{
	this->keys = std::move(keys);
}

void Mouse::Key_pressOnce::events()
{
	pressed = false;

	if (isPressed())
		pressed = true;
}

bool Mouse::Key_pressOnce::pressedOnce()
{
	if (!flag_pressed_once && pressed)
	{
		pressed_once = true;
		flag_pressed_once = true;

	}
	else if (flag_pressed_once)
	{
		pressed_once = false;

		if (!pressed)
			flag_pressed_once = false;
	}

	return pressed_once;
}

void Mouse::Key_pressOnce::reset()
{

}

bool Mouse::Key_pressOnce::isPressed() const
{
	for (auto& i : keys)
		if (!mouse_keys[int(i)])
			return false;

	return true;
}*/
