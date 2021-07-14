#include "Keyboard.h"

Key Keyboard::key_state{ Key::NONE };
Key Keyboard::mod_state{ Key::NONE };

const Uint8* Keyboard::keyboard{ SDL_GetKeyboardState(nullptr) };
bool Keyboard::pressed_once[1000]{};
bool Keyboard::flag_pressed_once[1000]{};

std::vector<Key> Keyboard::pressed_keys;

std::vector<Key> Keyboard::keys_pressOnce;

Keyboard::Shortcut_keys Keyboard::cntrl_z{
	{ Key::LCNTRL, Key::Z }
};

Keyboard::Shortcut_keys Keyboard::cntrl_y{
	{ Key::LCNTRL, Key::Y }
};

Keyboard::Shortcut_keys Keyboard::escape{
	{ Key::ESCAPE }
};

void Keyboard::switch_digits_up(SDL_Keycode& code)
{
}

#include <iostream>
using std::cout;

void Keyboard::switch_keys_down(SDL_Event* ev)
{
	switch_liters(ev->key.keysym.sym);
	switch_others(ev->key.keysym.sym);
	switch_digits(ev->key.keysym.sym);
}

void Keyboard::switch_keys_up(SDL_Event* ev)
{
	mod_state = { Key::NONE };

	switch_liters_up(ev->key.keysym.sym);
	switch_others_up(ev->key.keysym.sym);

	//key_state = { Key::NONE };
	//cntrl_y.reset();
	//cntrl_z.reset();
	//escape.reset();
}

void Keyboard::INIT()
{
	using k = Key;

	keys_pressOnce = {
		Key::NONE, k::A, k::B, k::C, k::D, k::E, k::F, k::G, k::H, k::I, k::J, k::K, k::L, k::M,
		k::N, k::O, k::P, k::Q, k::R, k::S, k::T, k::U, k::V, k::W, k::X, k::Y, k::Z,
		k::SPACE, k::ENTER, k::DELETE, k::CAPS_LOCK, k::ESCAPE, k::BACKSPACE, k::SHIFT, k::LCNTRL, k::RSHIFT,
		k::n1, k::n2, k::n3, k::n4, k::n5, k::n6, k::n7, k::n8, k::n9, k::n0,
	};
}

void Keyboard::events(SDL_Event* ev)
{
	key_state = Key::NONE;

	switch (ev->type) {
	case SDL_KEYDOWN:
		switch_keys_down(ev);
		break;
	case SDL_KEYUP:
		switch_keys_up(ev);
		break;
	}

	/*cntrl_z.events();
	cntrl_y.events();
	*/

	//escape.events();
}

void Keyboard::events_indp()
{

}

void Keyboard::switch_liters(SDL_Keycode & code)
{
	switch (code)
	{
	case SDLK_a:
		key_state = Key::A;
		break;
	case SDLK_b:
		key_state = Key::B;
		break;
	case SDLK_c:
		key_state = Key::C;
		break;
	case SDLK_d:
		key_state = Key::D;
		break;
	case SDLK_e:
		key_state = Key::E;
		break;
	case SDLK_f:
		key_state = Key::F;
		break;
	case SDLK_g:
		key_state = Key::G;
		break;
	case SDLK_h:
		key_state = Key::H;
		break;
	case SDLK_i:
		key_state = Key::I;
		break;
	case SDLK_j:
		key_state = Key::J;
		break;
	case SDLK_k:
		key_state = Key::K;
		break;
	case SDLK_l:
		key_state = Key::L;
		break;
	case SDLK_m:
		key_state = Key::M;
		break;
	case SDLK_n:
		key_state = Key::N;
		break;
	case SDLK_o:
		key_state = Key::O;
		break;
	case SDLK_p:
		key_state = Key::P;
		break;
	case SDLK_q:
		key_state = Key::Q;
		break;
	case SDLK_r:
		key_state = Key::R;
		break;
	case SDLK_s:
		key_state = Key::S;
		break;
	case SDLK_t:
		key_state = Key::T;
		break;
	case SDLK_u:
		key_state = Key::U;
		break;
	case SDLK_v:
		key_state = Key::V;
		break;
	case SDLK_w:
		key_state = Key::W;
		break;
	case SDLK_x:
		key_state = Key::X;
		break;
	case SDLK_y:
		key_state = Key::Y;
		break;
	case SDLK_z:
		key_state = Key::Z;
		break;
	}
}

void Keyboard::switch_others(SDL_Keycode & code)
{
	switch (code)
	{
	case SDLK_SPACE:
		key_state = Key::SPACE;
		break;
	case SDLK_ESCAPE:
		key_state = Key::ESCAPE;
		break;
	case SDLK_KP_ENTER:
		key_state = Key::ENTER;
		break;
	case SDLK_BACKSPACE:
		key_state = Key::BACKSPACE;
		break;
	case SDLK_DELETE:
		key_state = Key::DELETE;
		break;
	case SDLK_LCTRL:
		key_state = Key::LCNTRL;
		break;
	}
}

void Keyboard::switch_digits(SDL_Keycode & code)
{
	switch (code)
	{
	case SDLK_0:
		key_state = Key::n0;
		break;
	case SDLK_1:
		key_state = Key::n1;
		break;
	case SDLK_2:
		key_state = Key::n2;
		break;
	case SDLK_3:
		key_state = Key::n3;
		break;
	case SDLK_4:
		key_state = Key::n4;
		break;
	case SDLK_5:
		key_state = Key::n5;
		break;
	case SDLK_6:
		key_state = Key::n6;
		break;
	case SDLK_7:
		key_state = Key::n7;
		break;
	case SDLK_8:
		key_state = Key::n8;
		break;
	case SDLK_9:
		key_state = Key::n9;
		break;
	}
}

void Keyboard::switch_liters_up(SDL_Keycode & code)
{
	key_state = Key::NONE;

	switch (code)
	{
	case SDLK_a:
		flag_pressed_once[int(Key::A)] = false;
		break;
	case SDLK_b:
		flag_pressed_once[int(Key::B)] = false;
		break;
	case SDLK_c:
		flag_pressed_once[int(Key::C)] = false;
		break;
	case SDLK_d:
		flag_pressed_once[int(Key::D)] = false;
		break;
	case SDLK_e:
		flag_pressed_once[int(Key::E)] = false;
		break;
	case SDLK_f:
		flag_pressed_once[int(Key::F)] = false;
		break;
	case SDLK_g:
		flag_pressed_once[int(Key::G)] = false;
		break;
	case SDLK_h:
		flag_pressed_once[int(Key::H)] = false;
		break;
	case SDLK_i:
		flag_pressed_once[int(Key::I)] = false;
		break;
	case SDLK_j:
		flag_pressed_once[int(Key::J)] = false;
		break;
	case SDLK_k:
		flag_pressed_once[int(Key::K)] = false;
		break;
	case SDLK_l:
		flag_pressed_once[int(Key::L)] = false;
		break;
	case SDLK_m:
		flag_pressed_once[int(Key::M)] = false;
		break;
	case SDLK_n:
		flag_pressed_once[int(Key::N)] = false;
		break;
	case SDLK_o:
		flag_pressed_once[int(Key::O)] = false;
		break;
	case SDLK_p:
		flag_pressed_once[int(Key::P)] = false;
		break;
	case SDLK_q:
		flag_pressed_once[int(Key::Q)] = false;
		break;
	case SDLK_r:
		flag_pressed_once[int(Key::R)] = false;
		break;
	case SDLK_s:
		flag_pressed_once[int(Key::S)] = false;
		break;
	case SDLK_t:
		flag_pressed_once[int(Key::T)] = false;
		break;
	case SDLK_u:
		flag_pressed_once[int(Key::U)] = false;
		break;
	case SDLK_v:
		flag_pressed_once[int(Key::V)] = false;
		break;
	case SDLK_w:
		flag_pressed_once[int(Key::W)] = false;
		break;
	case SDLK_x:
		flag_pressed_once[int(Key::X)] = false;
		break;
	case SDLK_y:
		flag_pressed_once[int(Key::Y)] = false;
		break;
	case SDLK_z:
		flag_pressed_once[int(Key::Z)] = false;
		break;
	}
}

void Keyboard::switch_others_up(SDL_Keycode & code)
{
	switch (code)
	{
	case SDLK_SPACE:

		break;
	case SDLK_ESCAPE:
		flag_pressed_once[int(Key::ESCAPE)] = false;
		break;
	case SDLK_KP_ENTER:

		break;
	case SDLK_BACKSPACE:

		break;
	case SDLK_DELETE:

		break;
	case SDLK_LCTRL:
		flag_pressed_once[int(Key::LCNTRL)] = false;
		break;
	}
}

bool Keyboard::is_CapsLock_toggled()
{
	int temp = SDL_GetModState();
	temp &= KMOD_CAPS; // lub temp = temp & KMOD_CAPS

	if (temp == SDL_Keymod::KMOD_CAPS)
		return true;
	return false;
}

bool Keyboard::pressedOnce(Key key)
{
	if (keyboard[int(key)])
	{
		if (!flag_pressed_once[int(key)])
		{
			flag_pressed_once[int(key)] = true;
			pressed_once[int(key)] = true;
		}
		else
			pressed_once[int(key)] = false;
	}
	else
		pressed_once[int(key)] = false;

	return pressed_once[int(key)];
}

bool Keyboard::pressedOnce(std::vector<Key> keys)
{
	/*
	// sprawdz najpierw czy wciœniête klawisze
	for (auto& key : keys)
		if (!keyboard[int(key)])
			return false;

	for (auto& key : keys)
		if (!pressedOnce(key))
			return false;

	return true;*/

	for (auto& key : keys)
		if (!keyboard[int(key)])
			return false;

	for (auto& key : keys)
		if (!pressedOnce(key))
			return false;

	return true;

}


Keyboard::Shortcut_keys::Shortcut_keys(const std::vector<Key>& k)
{
	keyboard_keys = Keyboard::getKeys();
	keys = k;
	pressed_once = Keyboard::getPressedOnce();

	for (auto& i : this->keys)
	{
		code |= int(i);
	}
}

void Keyboard::Shortcut_keys::events()
{
	reset();

	if (isPressed()) {
		pressed = true;

		if (!flag_pressed_once) {
			flag_pressed_once = true;

			pressed_once[code] = true;
		}
	}
	else
		flag_pressed_once = false;
}

bool Keyboard::Shortcut_keys::pressedOnce()
{
	return pressed_once[code];
}

void Keyboard::Shortcut_keys::reset()
{
	pressed = false;
	pressed_once[code] = false;
}

bool Keyboard::Shortcut_keys::isPressed() const
{
	for (auto & i : keys)
		if (!keyboard[int(i)])
			return false;

	return true;
}
