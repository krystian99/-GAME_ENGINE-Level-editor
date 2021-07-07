#include "Object.h"
#include "Video_Info.h"

void Object::events()
{
	if (Mouse::is_inPOS(get_position()))
	{
		mouse_over = true;

		on_mouseOver();

		mouse_handler();
		keyboard_handler();
	}
	else if (mouse_over) {
		mouse_over = false;
		on_mouseOut();
	}
}

void Object::mouseOver_deactivate()
{
	on_mouseOut();
}

void Object::keyboardEvents_1hit()
{
	switch (Keyboard::get_currentKey())
	{
	case Key::A:
		on_keyboardKey_A_1hit();
		break;
	case Key::B:
		on_keyboardKey_B_1hit();
		break;
	case Key::C:
		on_keyboardKey_C_1hit();
		break;
	case Key::D:
		on_keyboardKey_D_1hit();
		break;
	case Key::E:
		on_keyboardKey_E_1hit();
		break;
	case Key::F:
		on_keyboardKey_F_1hit();
		break;
	case Key::G:
		on_keyboardKey_G_1hit();
		break;
	case Key::H:
		on_keyboardKey_H_1hit();
		break;
	case Key::I:
		on_keyboardKey_I_1hit();
		break;
	case Key::J:
		on_keyboardKey_J_1hit();
		break;
	case Key::K:
		on_keyboardKey_K_1hit();
		break;
	case Key::L:
		on_keyboardKey_L_1hit();
		break;
	case Key::M:
		on_keyboardKey_M_1hit();
		break;
	case Key::N:
		on_keyboardKey_N_1hit();
		break;
	case Key::O:
		on_keyboardKey_O_1hit();
		break;
	case Key::P:
		on_keyboardKey_P_1hit();
		break;
	case Key::Q:
		on_keyboardKey_Q_1hit();
		break;
	case Key::R:
		on_keyboardKey_R_1hit();
		break;
	case Key::S:
		on_keyboardKey_S_1hit();
		break;
	case Key::T:
		on_keyboardKey_T_1hit();
		break;
	case Key::U:
		on_keyboardKey_U_1hit();
		break;
	case Key::V:
		on_keyboardKey_V_1hit();
		break;
	case Key::W:
		on_keyboardKey_W_1hit();
		break;
	case Key::X:
		on_keyboardKey_X_1hit();
		break;
	case Key::Y:
		on_keyboardKey_Y_1hit();
		break;
	case Key::Z:
		on_keyboardKey_Z_1hit();
		break;
	case Key::DELETE:
		on_keyboardKey_DELETE_1hit();
		break;
	}
}

void Object::mouse_handler()
{
	if (Mouse::isUpdated()) {
		if (Mouse::pressedOnce(Mouse_key::L_BUTTON))
			on_mouseL1hit();
		else if (Mouse::pressedOnce(Mouse_key::R_BUTTON))
			on_mouseR1hit();
		else if (Mouse::pressedOnce(Mouse_key::MID_BUTTON))
			on_mouseW1hit();
	}
}

void Object::keyboard_handler()
{
	if (!Keyboard::is_pressedKey_once(Key::NONE))
		keyboardEvents_1hit();
}
