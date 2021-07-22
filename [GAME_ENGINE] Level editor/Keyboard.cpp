#include "Keyboard.h"

Key Keyboard::key_state{ Key::NONE };
Key Keyboard::key_state_up{ Key::NONE };
Key Keyboard::mod_state{ Key::NONE };

Key_pressOnce_s<Key> Keyboard::key_pressOnce_s;

const Uint8* Keyboard::keyboard{ SDL_GetKeyboardState(nullptr) };
bool Keyboard::flag_pressed_once[1000]{};

void Keyboard::switch_digits_up(SDL_Keycode& code)
{
	switch (code)
	{
	case SDLK_0:
		key_state_up = Key::n0;
		break;
	case SDLK_1:
		key_state_up = Key::n1;
		break;
	case SDLK_2:
		key_state_up = Key::n2;
		break;
	case SDLK_3:
		key_state_up = Key::n3;
		break;
	case SDLK_4:
		key_state_up = Key::n4;
		break;
	case SDLK_5:
		key_state_up = Key::n5;
		break;
	case SDLK_6:
		key_state_up = Key::n6;
		break;
	case SDLK_7:
		key_state_up = Key::n7;
		break;
	case SDLK_8:
		key_state_up = Key::n8;
		break;
	case SDLK_9:
		key_state_up = Key::n9;
		break;
	}
}

//#include <iostream>
//using std::cout;

void Keyboard::switch_keys_down(SDL_Event* ev)
{
	auto key_code = ev->key.keysym.sym;

	// przydatne dla wpisywania czegoœ do input_buttona
	switch_liters(key_code);
	switch_others(key_code);
	switch_digits(key_code);

	if (!flag_pressed_once[int(key_state)]) {
		//cout << "Wcisnieto cos raz!\n";
		flag_pressed_once[int(key_state)] = true;
		key_pressOnce_s.switch_keysDown(key_state);
	}
}

void Keyboard::switch_keys_up(SDL_Event* ev)
{
	mod_state = { Key::NONE };

	auto key_code = ev->key.keysym.sym;

	switch_liters_up(key_code);
	switch_others_up(key_code);
	switch_digits_up(key_code);

	flag_pressed_once[int(key_state_up)] = false;

	key_pressOnce_s.switch_keysUp(key_state_up);
}

void Keyboard::events(SDL_Event* ev)
{
	key_state = Key::NONE;
	key_state_up = Key::NONE;

	switch (ev->type) {
	case SDL_KEYDOWN:
		switch_keys_down(ev);
		break;
	case SDL_KEYUP:
		switch_keys_up(ev);
		break;
	}

	key_pressOnce_s.events();
}

Key Keyboard::get_actualKey()
{
	return key_pressOnce_s.get_pressed1_key();
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
	case SDLK_RETURN:
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
	case SDLK_LSHIFT:
		key_state = Key::LSHIFT;
		break;
	case SDLK_RSHIFT:
		key_state = Key::RSHIFT;
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
	switch (code)
	{
	case SDLK_a:
		key_state_up = Key::A;
		break;
	case SDLK_b:
		key_state_up = Key::B;
		break;
	case SDLK_c:
		key_state_up = Key::C;
		break;
	case SDLK_d:
		key_state_up = Key::D;
		break;
	case SDLK_e:
		key_state_up = Key::E;
		break;
	case SDLK_f:
		key_state_up = Key::F;
		break;
	case SDLK_g:
		key_state_up = Key::G;
		break;
	case SDLK_h:
		key_state_up = Key::H;
		break;
	case SDLK_i:
		key_state_up = Key::I;
		break;
	case SDLK_j:
		key_state_up = Key::J;
		break;
	case SDLK_k:
		key_state_up = Key::K;
		break;
	case SDLK_l:
		key_state_up = Key::L;
		break;
	case SDLK_m:
		key_state_up = Key::M;
		break;
	case SDLK_n:
		key_state_up = Key::N;
		break;
	case SDLK_o:
		key_state_up = Key::O;
		break;
	case SDLK_p:
		key_state_up = Key::P;
		break;
	case SDLK_q:
		key_state_up = Key::Q;
		break;
	case SDLK_r:
		key_state_up = Key::R;
		break;
	case SDLK_s:
		key_state_up = Key::S;
		break;
	case SDLK_t:
		key_state_up = Key::T;
		break;
	case SDLK_u:
		key_state_up = Key::U;
		break;
	case SDLK_v:
		key_state_up = Key::V;
		break;
	case SDLK_w:
		key_state_up = Key::W;
		break;
	case SDLK_x:
		key_state_up = Key::X;
		break;
	case SDLK_y:
		key_state_up = Key::Y;
		break;
	case SDLK_z:
		key_state_up = Key::Z;
		break;
	}
}

void Keyboard::switch_others_up(SDL_Keycode & code)
{
	switch (code)
	{
	case SDLK_SPACE:
		key_state_up = Key::SPACE;
		break;
	case SDLK_ESCAPE:
		key_state_up = Key::ESCAPE;
		break;
	case SDLK_RETURN:
		key_state_up = Key::ENTER;
		break;
	case SDLK_BACKSPACE:
		key_state_up = Key::BACKSPACE;
		break;
	case SDLK_DELETE:
		key_state_up = Key::DELETE;
		break;
	case SDLK_LCTRL:
		key_state_up = Key::LCNTRL;
		break;
	case SDLK_LSHIFT:
		key_state_up = Key::LSHIFT;
		break;
	case SDLK_RSHIFT:
		key_state_up = Key::RSHIFT;
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

bool Keyboard::is_pressedOnce(Key key)
{
	return key_pressOnce_s.is_pressedOnce(key);
}

bool Keyboard::is_pressedOnce(std::vector<Key> keys)
{
	return key_pressOnce_s.is_pressedOnce(keys);
}
