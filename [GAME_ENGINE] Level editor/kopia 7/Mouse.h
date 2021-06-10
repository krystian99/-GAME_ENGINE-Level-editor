#pragma once
#include <SDL_events.h>
#include <SDL_mouse.h>

class Mouse // Mouse handler
{
public:
	// Aktualizuje pozycjê myszki
	static void update(SDL_Event *);

	// Zwraca kordynaty myszki
	static int getMousePOSx() { return mX; }
	static int getMousePOSy() { return mY; }

	// Zwraca stany klawiszów
	static bool get_lButton_State() { return lButtonPressed; }
	static bool get_rButton_State() { return rButtonPressed; }
	static bool get_midButton_State() { return midButtonPressed; }

	static const int & getWheelMoves() { return wheel_moves; }

	// Stany kó³ka myszki
	static bool getWheelUpState() { return mWheelUp; }
	static bool getWheelDownState() { return mWheelDown; }

	// Rysuj pole
	void DrawRect(int width, int height);
private:
	Mouse() {} // tworzenie obiektów jest wy³¹czone

	// Sprawdza czy klawisze wcisniête
	static void switch_buttons_down(SDL_Event *);
	static void switch_buttons_up(SDL_Event *);
	static void switch_motion_wheel_FLAG(SDL_Event *);
private:
	static bool mMotion; // Poruszono myszk¹?

	static bool mWheelUp, mWheelDown;

	static bool lButtonPressed, rButtonPressed, midButtonPressed;

	static int wheel_moves;

	static int wheel_used;

	static int mX, mY; // kordynaty myszki
};

