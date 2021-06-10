#pragma once

union SDL_Event;

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

	static const int & getX() { return mX; }
	static const int & getY() { return mY; }

	static const int & getR_x() { return mX_r; }
	static const int & getR_y() { return mY_r; }

	static const bool & is_pressedL() { return l_pressed; }

	static const Mouse_key & getBt_state() { return key_state; }
	static const Mouse_wheel & getWheelState() { return wheel_state; }
private:
	static void switch_buttons_down(SDL_Event *);

	static void switch_motion_wheel_FLAG(SDL_Event *);
private:
	static Mouse_key key_state;
	static Mouse_wheel wheel_state;

	static bool l_pressed;

	static int mX_r, mY_r; // kordynaty poprzednie przed zaktualizowaniem zdarzeñ - SDL_PollEvent(&event_handler);
	static int mX, mY; // kordynaty myszki
};