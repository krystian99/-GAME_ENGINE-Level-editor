#pragma once
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <vector>

enum class Key {
	NONE,
	Q = SDL_SCANCODE_Q, W = SDL_SCANCODE_W, E = SDL_SCANCODE_E, R = SDL_SCANCODE_R, T = SDL_SCANCODE_T, Y = SDL_SCANCODE_Y, 
	U = SDL_SCANCODE_U, I = SDL_SCANCODE_I, O = SDL_SCANCODE_O, P = SDL_SCANCODE_P, 
	A = SDL_SCANCODE_A, S = SDL_SCANCODE_S, D = SDL_SCANCODE_D, F = SDL_SCANCODE_F, G = SDL_SCANCODE_G, H = SDL_SCANCODE_H, 
	J = SDL_SCANCODE_J, K = SDL_SCANCODE_K, L = SDL_SCANCODE_L, Z = SDL_SCANCODE_Z, X = SDL_SCANCODE_X, C = SDL_SCANCODE_C,
	V = SDL_SCANCODE_V, B = SDL_SCANCODE_B, N = SDL_SCANCODE_N, M = SDL_SCANCODE_M,
	SPACE = SDL_SCANCODE_SPACE, ENTER = SDL_SCANCODE_RETURN, DELETE = SDL_SCANCODE_DELETE, 
	CAPS_LOCK = SDL_SCANCODE_CAPSLOCK, ESCAPE = SDL_SCANCODE_ESCAPE, BACKSPACE = SDL_SCANCODE_BACKSPACE, 
	SHIFT = SDL_SCANCODE_LSHIFT,
	n1 = SDL_SCANCODE_1, n2 = SDL_SCANCODE_2, n3 = SDL_SCANCODE_3, n4 = SDL_SCANCODE_4, n5 = SDL_SCANCODE_5, n6 = SDL_SCANCODE_6, 
	n7 = SDL_SCANCODE_7, n8 = SDL_SCANCODE_8, n9 = SDL_SCANCODE_9, n0 = SDL_SCANCODE_0,
	LCNTRL = SDL_SCANCODE_LCTRL,
	RSHIFT = SDL_SCANCODE_RSHIFT
}; // n - number

class Keyboard
{
public:
	static void events(SDL_Event * ev);

	static bool is_CapsLock_toggled();

	/* Musi zostaæ wywo³ane przez klasê zarz¹dzaj¹ca daym stanem
	przyk³ad: MenuStart->events()
	Wtedy klasa zarz¹dzaj¹ca przekierowuje dalej stany*/
	static bool is_pressed_LCNTRL_Z() { return cntrl_z.pressedOnce(); }

	/* Musi zostaæ wywo³ane przez klasê zarz¹dzaj¹ca daym stanem
	przyk³ad: MenuStart->events()
	Wtedy klasa zarz¹dzaj¹ca przekierowuje dalej stany*/
	static bool is_pressed_LCNTRL_Y() { return cntrl_y.pressedOnce(); }

	static bool is_pressedEscape() { return escape.pressedOnce(); }

	static bool is_pressedBackspace() { return key_state == Key::BACKSPACE; }

	static bool is_pressedShift() { return keyboard[int(Key::SHIFT)] || keyboard[int(Key::RSHIFT)]; }

	static bool is_pressedKey(Key k) { return keyboard[int(k)]; }

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
	class Shortcut_keys
	{
	public:
		Shortcut_keys(const std::vector<Key> &);

		void events();

		bool is_pressed() const { return pressed; }

		bool pressedOnce();

		void reset();
	private:
		bool isPressed() const;
	private:
		bool pressed{ false };

		std::vector<Key> keys;

		bool flag_pressed_once{ false };
		bool pressed_once{ false };
	};

	static Shortcut_keys cntrl_z, cntrl_y, escape;

	static const Uint8* keyboard;

	static Key key_state;
	static Key mod_state;
};
