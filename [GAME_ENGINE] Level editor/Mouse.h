#pragma once
#include "Rect.h"
#include <SDL_rect.h>
#include <SDL_events.h>

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

	static bool pressed_Lbutton() { return l_pressed; }

	static bool is_inPOS(const SDL_Rect & pos);
	static bool clickedPoint_inPOS(const Rect &);

	// klikniêto przycisk lub ruszono myszk¹
	static bool isUpdated() { return updated || moved(); }

	static bool moved();

	static const SDL_Point & get_clickedPoint() { return clicked_point; }
	//static const bool & check_clickedPoint(const SDL_Rect & pos);

	static const Mouse_key & getBt_state() { return key_state; }
	static const Mouse_wheel & getWheelState() { return wheel_state; }
private:
	static void switch_buttons_down(SDL_Event *);

	static void switch_motion_wheel_FLAG(SDL_Event *);
private:
	static Mouse_key key_state;
	static Mouse_wheel wheel_state;

	static SDL_Point clicked_point; // gdy zostanie klikniêty lewy klawisz i jest trzymany, to zapisz wspó³rzêdne punktu 

	static bool l_pressed;

	static bool updated;

	static int mX_r, mY_r; // kordynaty poprzednie przed zaktualizowaniem zdarzeñ - SDL_PollEvent(&event_handler);
	static int mX, mY; // kordynaty myszki
};