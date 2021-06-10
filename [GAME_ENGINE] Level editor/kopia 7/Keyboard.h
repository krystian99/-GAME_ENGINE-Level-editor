#pragma once
#include <SDL_events.h>
#include <SDL_keyboard.h>

class Keyboard
{
public:
	// Aktualizuje stan klawiszy
	static void update(SDL_Event *);

	// Zwraca stan klawiszy
	static bool get_D_State() { return Key_D_pressed; }

	static bool get_A_State() { return Key_A_pressed; }

	static bool get_SPACE_State() { return Key_SPACE_pressed; }

	static bool get_ENTER_State() { return Key_ENTER_pressed; }

	static bool get_ESCAPE_State() { return Key_ESCAPE_pressed; }
private:
	Keyboard() {}
	// Stany zdarzeñ - wciœniêty, czy opuszczony klawisz
	static void switch_keys_up(SDL_Event * ev);
	static void switch_keys_down(SDL_Event * ev);

	// Stany klawiszy - wciœniêty, czy opuszczony
	static void set_D_FLAG_T() { Key_D_pressed = true; }
	static void set_D_FLAG_F() { Key_D_pressed = false; }

	static void set_A_FLAG_T() { Key_A_pressed = true; }
	static void set_A_FLAG_F() { Key_A_pressed = false; }

	static void set_SPACE_FLAG_T() { Key_SPACE_pressed = true; }
	static void set_SPACE_FLAG_F() { Key_SPACE_pressed = false; }

	static void set_ENTER_FLAG_T() { Key_ENTER_pressed = true; }
	static void set_ENTER_FLAG_F() { Key_ENTER_pressed = false; }

	static void set_ESCAPE_FLAG_T() { Key_ESCAPE_pressed = true; }
	static void set_ESCAPE_FLAG_F() { Key_ESCAPE_pressed = false; }
private:
	static bool Key_D_pressed, Key_A_pressed, Key_SPACE_pressed, Key_ESCAPE_pressed, Key_ENTER_pressed;
};

