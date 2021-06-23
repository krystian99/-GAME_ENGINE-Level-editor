#include "Keyboard.h"

Key Keyboard::key_state{ Key::NONE };
Key Keyboard::mod_state{ Key::NONE };
Key Keyboard::backspace_state{ Key::NONE };

const Uint8* Keyboard::keyboard{ nullptr };

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

void Keyboard::switch_keys_down(SDL_Event* ev)
{
	switch_liters(ev->key.keysym.sym);
	switch_others(ev->key.keysym.sym);
	switch_digits(ev->key.keysym.sym);
}

void Keyboard::switch_keys_up(SDL_Event* ev)
{
	mod_state = { Key::NONE };
	key_state = { Key::NONE };
}

void Keyboard::events(SDL_Event* ev)
{
	key_state = Key::NONE;
	backspace_state = Key::NONE;

	keyboard = SDL_GetKeyboardState(nullptr);

	cntrl_z.events();
	cntrl_y.events();
	escape.events();

	switch (ev->type) {
	case SDL_KEYDOWN:
		switch_keys_down(ev);
		break;
	case SDL_KEYUP:
		switch_keys_up(ev);
		break;
	}
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
	/*case SDLK_BACKSPACE:
		key_state = Key::BACKSPACE;
		break;*/
	}
}

void Keyboard::switch_others(SDL_Keycode & code)
{
	if (code == SDLK_BACKSPACE) 
		backspace_state = Key::BACKSPACE;

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
	case SDLK_BACKSPACE:
		key_state = Key::BACKSPACE;
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
}

void Keyboard::switch_others_up(SDL_Keycode & code)
{
	mod_state = Key::NONE;
}

bool Keyboard::is_CapsLock_toggled()
{
	int temp = SDL_GetModState();
	temp &= KMOD_CAPS; // lub temp = temp & KMOD_CAPS

	if (temp == SDL_Keymod::KMOD_CAPS)
		return true;
	return false;
}


Keyboard::Shortcut_keys::Shortcut_keys(const std::vector<Key>& keys)
{
	this->keys = std::move(keys);
}

void Keyboard::Shortcut_keys::events()
{
	pressed = false;

	if (isPressed())
		pressed = true;
}

bool Keyboard::Shortcut_keys::pressedOnce()
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

bool Keyboard::Shortcut_keys::isPressed() const
{
	for (auto & i : keys)
		if (!keyboard[int(i)])
			return false;

	return true;
}
