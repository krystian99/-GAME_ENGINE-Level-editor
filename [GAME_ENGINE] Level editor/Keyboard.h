#pragma once
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <vector>
#include "Key_pressOnce_s.h"

enum class Key {
	NONE,
	Q = SDL_SCANCODE_Q, W = SDL_SCANCODE_W, E = SDL_SCANCODE_E, R = SDL_SCANCODE_R, T = SDL_SCANCODE_T, Y = SDL_SCANCODE_Y, 
	U = SDL_SCANCODE_U, I = SDL_SCANCODE_I, O = SDL_SCANCODE_O, P = SDL_SCANCODE_P, 
	A = SDL_SCANCODE_A, S = SDL_SCANCODE_S, D = SDL_SCANCODE_D, F = SDL_SCANCODE_F, G = SDL_SCANCODE_G, H = SDL_SCANCODE_H, 
	J = SDL_SCANCODE_J, K = SDL_SCANCODE_K, L = SDL_SCANCODE_L, Z = SDL_SCANCODE_Z, X = SDL_SCANCODE_X, C = SDL_SCANCODE_C,
	V = SDL_SCANCODE_V, B = SDL_SCANCODE_B, N = SDL_SCANCODE_N, M = SDL_SCANCODE_M,
	SPACE = SDL_SCANCODE_SPACE, ENTER = SDL_SCANCODE_RETURN, DELETE = SDL_SCANCODE_DELETE, 
	CAPS_LOCK = SDL_SCANCODE_CAPSLOCK, ESCAPE = SDL_SCANCODE_ESCAPE, BACKSPACE = SDL_SCANCODE_BACKSPACE, 
	LSHIFT = SDL_SCANCODE_LSHIFT,
	n1 = SDL_SCANCODE_1, n2 = SDL_SCANCODE_2, n3 = SDL_SCANCODE_3, n4 = SDL_SCANCODE_4, n5 = SDL_SCANCODE_5, n6 = SDL_SCANCODE_6, 
	n7 = SDL_SCANCODE_7, n8 = SDL_SCANCODE_8, n9 = SDL_SCANCODE_9, n0 = SDL_SCANCODE_0,
	LCNTRL = SDL_SCANCODE_LCTRL,
	RSHIFT = SDL_SCANCODE_RSHIFT
}; // n - number

enum class Key_queue {
	NONE,
	Q = SDLK_q, W = SDLK_w, E = SDLK_e, R = SDLK_r, T = SDLK_t, Y = SDLK_y,
	U = SDLK_u, I = SDLK_i, O = SDLK_o, P = SDLK_p,
	A = SDLK_a, S = SDLK_s, D = SDLK_d, F = SDLK_f, G = SDLK_g, H = SDLK_h,
	J = SDLK_j, K = SDLK_k, L = SDLK_l, Z = SDLK_z, X = SDLK_x, C = SDLK_c,
	V = SDLK_v, B = SDLK_b, N = SDLK_n, M = SDLK_m,
	SPACE = SDLK_SPACE, ENTER = SDLK_RETURN, DELETE = SDLK_DELETE,
	CAPS_LOCK = SDLK_CAPSLOCK, ESCAPE = SDLK_ESCAPE, BACKSPACE = SDLK_BACKSPACE,
	SHIFT = SDLK_LSHIFT,
	n1 = SDLK_1, n2 = SDLK_2, n3 = SDLK_3, n4 = SDLK_4, n5 = SDLK_5, n6 = SDLK_6,
	n7 = SDLK_7, n8 = SDLK_8, n9 = SDLK_9, n0 = SDLK_0,
	LCNTRL = SDLK_LCTRL,
	RSHIFT = SDLK_RSHIFT
}; // n - number

class Keyboard
{
public:
	static void INIT(){}

	static void events(SDL_Event * ev);

	static bool is_CapsLock_toggled();

	static bool is_keyPressed() { return !key_pressOnce_s.empty(); }

	static bool is_pressedOnce(Key key);

	static bool is_pressedOnce(std::vector<Key> keys);

	static bool is_pressedBackspace() { return key_state == Key::BACKSPACE; }

	static bool is_pressedShift() { return keyboard[int(Key::LSHIFT)] || keyboard[int(Key::RSHIFT)]; }

	static bool is_pressedKey(Key k) { return keyboard[int(k)]; }

	//static const Uint8* getKeys() { return keyboard; }

	static bool is_pressedKey_once(Key k) { return key_state == k; }

	static const Key & get_currentKey() { return key_state; }
	static const Key & getModState() { return mod_state; }
private:
	static void switch_liters(SDL_Keycode & code);
	static void switch_others(SDL_Keycode & code);
	static void switch_digits(SDL_Keycode & code);

	static void switch_liters_up(SDL_Keycode & code);
	static void switch_others_up(SDL_Keycode & code);
	static void switch_digits_up(SDL_Keycode & code);

	static void switch_keys_down(SDL_Event * ev);
	static void switch_keys_up(SDL_Event * ev);
private:
	static Key_pressOnce_s<enum class Key> key_pressOnce_s;

	static bool flag_pressed_once[1000];

	static const Uint8* keyboard;

	static Key key_state, key_state_up;
	static Key mod_state;
};
