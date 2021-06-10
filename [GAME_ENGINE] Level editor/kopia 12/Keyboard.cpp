#include "Keyboard.h"
#include "Setup.h"

Key Keyboard::key_state{ Key::NONE };
Key Keyboard::mod_state{ Key::NONE };
Key Keyboard::backspace_state{ Key::NONE };

void Keyboard::switchMod()
{
	//if (mod_state )
}

void Keyboard::switch_liters(SDL_Keycode & code)
{
	switch (code)
	{
	case SDLK_a:
		key_state = { Key::A };
		break;
	case SDLK_b:
		key_state = { Key::B };
		break;
	case SDLK_c:
		key_state = { Key::C };
		break;
	case SDLK_d:
		key_state = { Key::D };
		break;
	case SDLK_e:
		key_state = { Key::E };
		break;
	case SDLK_f:
		key_state = { Key::F };
		break;
	case SDLK_g:
		key_state = { Key::G };
		break;
	case SDLK_h:
		key_state = { Key::H };
		break;
	case SDLK_i:
		key_state = { Key::I };
		break;
	case SDLK_j:
		key_state = { Key::J };
		break;
	case SDLK_k:
		key_state = { Key::K };
		break;
	case SDLK_l:
		key_state = { Key::L };
		break;
	case SDLK_m:
		key_state = { Key::M };
		break;
	case SDLK_n:
		key_state = { Key::N };
		break;
	case SDLK_o:
		key_state = { Key::O };
		break;
	case SDLK_p:
		key_state = { Key::P };
		break;
	case SDLK_q:
		key_state = { Key::Q };
		break;
	case SDLK_r:
		key_state = { Key::R };
		break;
	case SDLK_s:
		key_state = { Key::S };
		break;
	case SDLK_t:
		key_state = { Key::T };
		break;
	case SDLK_u:
		key_state = { Key::U };
		break;
	case SDLK_v:
		key_state = { Key::V };
		break;
	case SDLK_w:
		key_state = { Key::W };
		break;
	case SDLK_x:
		key_state = { Key::X };
		break;
	case SDLK_y:
		key_state = { Key::Y };
		break;
	case SDLK_z:
		key_state = { Key::Z };
		break;
	case SDLK_BACKSPACE:
		key_state = { Key::BACKSPACE };
		break;
	}
}

void Keyboard::switch_others(SDL_Keycode & code)
{
	if (code == SDLK_BACKSPACE) backspace_state = Key::BACKSPACE;

	switch (code)
	{
	case SDLK_SPACE:
		key_state = { Key::SPACE };
		break;
	case SDLK_ESCAPE:
		key_state = { Key::ESCAPE };
	case SDLK_CAPSLOCK:
		key_state = { Key::CAPS_LOCK };
		break;
	/*case SDLK_BACKSPACE:
		key_state = { Key::BACKSPACE };
		break;*/
	case SDLK_KP_ENTER:
		key_state = { Key::ENTER };
		break;
	case SDLK_LSHIFT: //case SDLK_RSHIFT:
		mod_state = { Key::SHIFT };
		break;
	}
}

void Keyboard::switch_liters_up(SDL_Keycode & code)
{
	switch (code)
	{
	case SDLK_a:
	case SDLK_b:
	case SDLK_c:
	case SDLK_d:
	case SDLK_e:
	case SDLK_f:
	case SDLK_g:
	case SDLK_h:
	case SDLK_i:
	case SDLK_j:
	case SDLK_k:
	case SDLK_l:
	case SDLK_m:
	case SDLK_n:
	case SDLK_o:
	case SDLK_p:
	case SDLK_q:
	case SDLK_r:
	case SDLK_s:
	case SDLK_t:
	case SDLK_u:
	case SDLK_v:
	case SDLK_w:
	case SDLK_x:
	case SDLK_y:
	case SDLK_z:
	case SDLK_BACKSPACE:
		key_state = { Key::NONE };
		break;
	}
}

void Keyboard::switch_others_up(SDL_Keycode & code)
{
	switch (code)
	{
	case SDLK_SPACE:
	case SDLK_ESCAPE:
	case SDLK_CAPSLOCK:
	case SDLK_KP_ENTER:
	case SDLK_LSHIFT: //case SDLK_RSHIFT:
		mod_state = { Key::NONE };
		break;
	}
}

void Keyboard::switch_keys_down(SDL_Event * ev)
{
	switch_liters(ev->key.keysym.sym);
	switch_others(ev->key.keysym.sym);
}

void Keyboard::switch_keys_up(SDL_Event * ev)
{
	switch_others_up(ev->key.keysym.sym);
	switch_liters_up(ev->key.keysym.sym);
}

void Keyboard::events(SDL_Event * ev)
{
	key_state = { Key::NONE };
	backspace_state = Key::NONE;
	//mod_state = { Key::NONE };
	switch (ev->type) {
	case SDL_KEYDOWN:
		switch_keys_down(ev);
		break;
	case SDL_KEYUP:
		switch_keys_up(ev);
		//key_state = { Key::NONE };
		//mod_state = { Key::NONE };
		break;
	}
	//backspace_state = Key::NONE;
}