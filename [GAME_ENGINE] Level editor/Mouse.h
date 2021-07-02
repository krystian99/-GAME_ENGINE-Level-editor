#pragma once
#include "Rect.h"
#include <SDL_rect.h>
#include <SDL_events.h>
#include <vector>
#include "Key_pressOnce.h"
#include "Mouse_keys.h"

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

	static bool is_inState(Mouse_key key) { return key_state == key; }

	static bool* getKEYS() { return keys; }

	static const bool & is_pressedL() { return keys[int(Mouse_key::L_BUTTON)]; }

	static bool pressedOnce(Mouse_key key);

	static bool is_pressedL_once() { return lButton_pressOnce.pressedOnce(); }

	static bool pressed_Lbutton() { return keys[int(Mouse_key::L_BUTTON)]; }

	static bool is_inPOS(const SDL_Rect & pos);
	static bool clickedPoint_inPOS(const Rect &);

	// klikni�to przycisk lub ruszono myszk�
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

	static Mouse_key key_state;
	static Mouse_wheel wheel_state;

	static SDL_Point clicked_point; // gdy zostanie klikni�ty lewy klawisz i jest trzymany, to zapisz wsp�rz�dne punktu 

	static bool keys[1000];

	static bool l_pressed, r_pressed, m_pressed;

	static bool updated;

	static int mX_r, mY_r; // kordynaty poprzednie przed zaktualizowaniem zdarze� - SDL_PollEvent(&event_handler);
	static int mX, mY; // kordynaty myszki
};
