#pragma once
#include <SDL_events.h>
#include <SDL_keyboard.h>

enum class Key {
	NONE,
	Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M,
	SPACE, ENTER, DELETE, CAPS_LOCK, ESCAPE, BACKSPACE, SHIFT,
	n1, n2, n3, n4, n5, n6, n7, n8, n9, n0

}; // n - number

class Keyboard
{
public:
	static void Init();
	static void events(SDL_Event * ev);

	static bool is_CapsLock_toggled() { 
		int temp = SDL_GetModState();
		temp &= KMOD_CAPS; // lub temp = temp & KMOD_CAPS

		if (temp == SDL_Keymod::KMOD_CAPS)
			return true;
		return false;
	}

	static const Key & getState() { return key_state; }
	static const Key & getModState() { return mod_state; }
	static const Key & getBackSpace() { return backspace_state; }
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
	static Key key_state;
	static Key mod_state;
	static Key backspace_state;
};