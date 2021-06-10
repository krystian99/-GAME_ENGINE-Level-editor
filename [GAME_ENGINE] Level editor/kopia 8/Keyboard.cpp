#include "Keyboard.h"

bool Keyboard::Key_A_pressed = false;
bool Keyboard::Key_ESCAPE_pressed = false;
bool Keyboard::Key_SPACE_pressed = false;
bool Keyboard::Key_D_pressed = false;
bool Keyboard::Key_ENTER_pressed = false;

void Keyboard::update(SDL_Event * ev)
{
	switch (ev->type) {
	case SDL_KEYDOWN:
		switch_keys_down(ev);
		break;
	case SDL_KEYUP:
		switch_keys_up(ev);
		break;
	}
}

void Keyboard::switch_keys_up(SDL_Event * ev)
{
	switch (ev->key.keysym.sym) {
	case SDLK_RETURN: // Enter key
		set_ENTER_FLAG_F();
		break;
	case SDLK_d:
		set_D_FLAG_F();
		break;
	case SDLK_a:
		set_A_FLAG_F();
		break;
	case SDLK_SPACE:
		set_SPACE_FLAG_F();
		break;
	case SDLK_ESCAPE:
		set_ESCAPE_FLAG_F();
	}
}

void Keyboard::switch_keys_down(SDL_Event * ev)
{
	switch (ev->key.keysym.sym) {
	case SDLK_KP_ENTER:
		set_ENTER_FLAG_T();
		break;
	case SDLK_d:
		set_D_FLAG_T();
		break;
	case SDLK_a:
		set_A_FLAG_T();
		break;
	case SDLK_SPACE:
		set_SPACE_FLAG_T();
		break;
	case SDLK_ESCAPE:
		set_ESCAPE_FLAG_T();
	}
}
