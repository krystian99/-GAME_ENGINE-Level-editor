#pragma once
#include <SDL_events.h>
#include <SDL_mouse.h>

enum class Mouse_key {
	NONE,
	L_BUTTON, R_BUTTON, MID_BUTTON
};
enum class Mouse_wheel {
	NONE,
	UP, DOWN
};
class Mouse
{
public:
	static void update(SDL_Event *);

	static int getMousePOSx() { return mX; }
	static int getMousePOSy() { return mY; }

	static const Mouse_key & getButtonState() { return state; }
	static const Mouse_wheel & getWheelState() { return state2; }
private:
	static void switch_buttons_down(SDL_Event *);
	static void switch_motion_wheel_FLAG(SDL_Event *);
private:
	static Mouse_key state;
	static Mouse_wheel state2;

	static int mX, mY; // kordynaty myszki
};

