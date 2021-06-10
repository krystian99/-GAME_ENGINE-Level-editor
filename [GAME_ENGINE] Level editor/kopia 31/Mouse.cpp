#include "Mouse.h"
#include <SDL_events.h>
#include <SDL_mouse.h>

int Mouse::mX = 0; // Obecna pozycja
int Mouse::mY = 0; // Obecna pozycja
int Mouse::mX_r = 0; // Obecna pozycja
int Mouse::mY_r = 0; // Obecna pozycja

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

void Mouse::switch_buttons_down(SDL_Event * ev)
{
	switch (ev->button.button) {
	case SDL_BUTTON_LEFT:
		key_state = Mouse_key::L_BUTTON;
		l_pressed = true;
		break;
	case SDL_BUTTON_RIGHT:
		key_state = Mouse_key::R_BUTTON;
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