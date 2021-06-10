#include "Mouse.h"
#include "Setup.h"

int Mouse::mX = 0; // Obecna pozycja
int Mouse::mY = 0; // Obecna pozycja

Mouse_key Mouse::state{ Mouse_key::NONE };
Mouse_wheel Mouse::state2{ Mouse_wheel::NONE };

void Mouse::update(SDL_Event * ev)
{
	state = Mouse_key::NONE;
	state2 = Mouse_wheel::NONE;

	SDL_GetMouseState(&mX, &mY);

	switch (ev->type) {
	case SDL_MOUSEBUTTONDOWN:
		switch_buttons_down(ev);
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
		state = Mouse_key::L_BUTTON;
		break;
	case SDL_BUTTON_RIGHT:
		state = Mouse_key::R_BUTTON;
		break;
	case SDL_BUTTON_MIDDLE:
		state = Mouse_key::MID_BUTTON;
		break;
	}
}

void Mouse::switch_motion_wheel_FLAG(SDL_Event * ev)
{
	switch (ev->wheel.direction) {
	case SDL_MOUSEWHEEL_NORMAL:
		if (ev->wheel.y < 0)
			state2 = Mouse_wheel::DOWN;
		else
			state2 = Mouse_wheel::UP;
		break;
	}
}