#pragma once
#include "Mouse.h"
#include "Keyboard.h"

class Module_Object
{
	bool is_mouseKey_1hit(Mouse_key key) const { return Mouse::is_pressedOnce(key); }
	bool is_keyboardKey_1hit(Key key) const { return Keyboard::is_pressedOnce(key); }

	void events();

	virtual ~Module_Object() {}
protected:
	virtual void on_mouseL1hit() {}
	virtual void on_mouseR1hit() {}
	virtual void on_mouseW1hit() {}

	virtual void on_mouseWheel_down_1hit() {}
	virtual void on_mouseWheel_up_1hit() {}

	virtual void on_mouseOver() {}
	virtual void on_mouseOut() {}

	virtual void on_mouseL_press() {}
	virtual void on_mouseR_press() {}
	virtual void on_mouseW_press() {}

	virtual void on_mouseL_pressUP() {}
	virtual void on_mouseR_pressUP() {}
	virtual void on_mouseW_pressUP() {}

	virtual void on_keyboardKey_A_1hit() {}
	virtual void on_keyboardKey_B_1hit() {}
	virtual void on_keyboardKey_C_1hit() {}
	virtual void on_keyboardKey_D_1hit() {}
	virtual void on_keyboardKey_E_1hit() {}
	virtual void on_keyboardKey_F_1hit() {}
	virtual void on_keyboardKey_G_1hit() {}
	virtual void on_keyboardKey_H_1hit() {}
	virtual void on_keyboardKey_I_1hit() {}
	virtual void on_keyboardKey_J_1hit() {}
	virtual void on_keyboardKey_K_1hit() {}
	virtual void on_keyboardKey_L_1hit() {}
	virtual void on_keyboardKey_M_1hit() {}
	virtual void on_keyboardKey_N_1hit() {}
	virtual void on_keyboardKey_O_1hit() {}
	virtual void on_keyboardKey_P_1hit() {}
	virtual void on_keyboardKey_Q_1hit() {}
	virtual void on_keyboardKey_R_1hit() {}
	virtual void on_keyboardKey_S_1hit() {}
	virtual void on_keyboardKey_T_1hit() {}
	virtual void on_keyboardKey_U_1hit() {}
	virtual void on_keyboardKey_V_1hit() {}
	virtual void on_keyboardKey_W_1hit() {}
	virtual void on_keyboardKey_X_1hit() {}
	virtual void on_keyboardKey_Y_1hit() {}
	virtual void on_keyboardKey_Z_1hit() {}

	virtual void on_keyboardKey_DELETE_1hit() {}
private:
	void reset_states();

	void keyboardEvents_1hit();

	void mouse_handler();
	void keyboard_handler();
private:
	bool mouse_over;

	bool flag_pressed[Mouse::MAX_KEY_ID]{};
};
