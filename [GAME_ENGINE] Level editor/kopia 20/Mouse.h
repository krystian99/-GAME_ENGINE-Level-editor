#pragma once
#include <SDL_events.h>
#include <SDL_mouse.h>

enum class Mouse_key {
	NONE,
	L_BUTTON, R_BUTTON, MID_BUTTON,
	RELEASED_L, RELEASED_R, RELEASED_M
};
enum class Mouse_wheel {
	NONE,
	UP, DOWN
};
class Mouse
{
public:
	static void update(SDL_Event *);

	static const int & getMousePOSx() { return mX; }
	static const int & getMousePOSy() { return mY; }

	static const int & getRecent_x() { return mX_r; }
	static const int & getRecent_y() { return mY_r; }

	static const bool & getLState() { return left_pressed; }
	static const bool & getRState() { return right_pressed; }

	static const Mouse_key & getButtonState() { return state; }
	static const Mouse_wheel & getWheelState() { return state2; }
private:
	static void switch_buttons_down(SDL_Event *);

	static void switch_motion_wheel_FLAG(SDL_Event *);
private:
	static Mouse_key state;
	static Mouse_wheel state2;

	static bool left_pressed;
	static bool right_pressed;

	static int mX_r, mY_r;
	static int mX, mY; // kordynaty myszki
};

