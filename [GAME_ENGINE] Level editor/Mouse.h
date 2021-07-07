#pragma once
#include "Rect.h"
#include <SDL_rect.h>
#include <SDL_events.h>
#include <vector>

class Key_pressOnce;

enum class Mouse_key {
	NONE = 1,
	L_BUTTON = 2, R_BUTTON = 4, MID_BUTTON = 8, WHEEL_UP = 16, WHEEL_DOWN = 32
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

	static const bool * getKeys() { return keys; }
	//static int* getCounts() { return counts; }

	static bool* get_pressedOnce() { return pressed_once; }

	static bool is_WheelState(Mouse_key st) { return keys[int(st)]; }

	static bool is_inState(Mouse_key key) { return key_state == key; }

	static const bool & is_pressedL() { return keys[int(Mouse_key::L_BUTTON)]; }

	static bool pressedOnce(Mouse_key key);

	static bool is_pressedL_once();
	static bool is_pressedR_once();

	static bool pressed_Lbutton() { return keys[int(Mouse_key::L_BUTTON)]; }

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
	static Key_pressOnce lButton_pressOnce, rButton_pressOnce, midButton_pressOnce;

	static Key_pressOnce wheelUP_pressOnce, wheelDOWN_pressOnce;

	static Mouse_key key_state;
	static Mouse_wheel wheel_state;

	static SDL_Point clicked_point; // gdy zostanie klikniêty lewy klawisz i jest trzymany, to zapisz wspó³rzêdne punktu 

	static bool keys[100];

	static bool pressed_once[100];

	static bool l_pressed, r_pressed, m_pressed;

	static bool updated;

	static int mX_r, mY_r; // kordynaty poprzednie przed zaktualizowaniem zdarzeñ - SDL_PollEvent(&event_handler);
	static int mX, mY; // kordynaty myszki
};
