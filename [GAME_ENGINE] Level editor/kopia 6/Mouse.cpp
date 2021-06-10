#include "Mouse.h"


int Mouse::mX = 0; // Obecna pozycja
int Mouse::mY = 0; // Obecna pozycja

int Mouse::wheel_moves = 0;

bool Mouse::lButtonPressed = false;
bool Mouse::rButtonPressed = false;
bool Mouse::midButtonPressed = false;
bool Mouse::mMotion = false;
bool Mouse::mWheelUp = false;
bool Mouse::mWheelDown = false;

int Mouse::wheel_used = false;

void Mouse::update(SDL_Event * ev)
{
	mWheelDown = false;
	mWheelUp = false;
	SDL_GetMouseState(&mX, &mY);
	switch (ev->type) {
	case SDL_MOUSEBUTTONDOWN:
		switch_buttons_down(ev);
		break;
	case SDL_MOUSEBUTTONUP:
		switch_buttons_up(ev);
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
		lButtonPressed = true;
		break;
	case SDL_BUTTON_RIGHT:
		rButtonPressed = true;
		break;
	case SDL_BUTTON_MIDDLE:
		midButtonPressed = true;
		break;
	}
}

void Mouse::switch_buttons_up(SDL_Event * ev)
{
	switch (ev->button.button) {
	case SDL_BUTTON_LEFT:
		lButtonPressed = false;
		break;
	case SDL_BUTTON_RIGHT:
		rButtonPressed = false;
		break;
	case SDL_BUTTON_MIDDLE:
		midButtonPressed = false;
		break;
	}
}

void Mouse::switch_motion_wheel_FLAG(SDL_Event * ev)
{
	switch (ev->wheel.direction) {
	case SDL_MOUSEWHEEL_NORMAL:
		if (ev->wheel.y < 0)
			mWheelDown = true;
		else
			mWheelUp = true;
		break;
	}
}
