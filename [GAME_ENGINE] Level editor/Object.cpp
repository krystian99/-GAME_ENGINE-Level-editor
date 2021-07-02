#include "Object.h"
#include "Video_Info.h"

Object::Object() :
	mouseL_button{ {Mouse_key::L_BUTTON} }, mouseR_button{ {Mouse_key::R_BUTTON} }, mouseM_button{ {Mouse_key::MID_BUTTON} }
{
}

Object::Object(Rect render_position)
	: Rect{ render_position }, mouseL_button{ {Mouse_key::L_BUTTON} }, mouseR_button{ {Mouse_key::R_BUTTON} }, mouseM_button{ {Mouse_key::MID_BUTTON} }
{

}

Object::Object(int x, int y, int w, int h) :
	mouseL_button{ {Mouse_key::L_BUTTON} }, mouseR_button{ {Mouse_key::R_BUTTON} }, mouseM_button{ {Mouse_key::MID_BUTTON} }
{
	set_position(x, y, w, h);
}

void Object::events()
{
	if (Mouse::is_inPOS(get_position()))
	{
		reset_states();

		mouse_over = true;

		on_mouseOver();

		mouse_handler();
		keyboard_handler();
	}
	else if (mouse_over) {
		reset_states();

		mouse_over = false;
		on_mouseOut();
	}
}

void Object::mouseOver_deactivate()
{
	on_mouseOut();
}

void Object::reset_states()
{
	mouse_key = Mouse_key::NONE;
	keyboard_key = Key::NONE;
}

void Object::mouseEvents_1hit() // jakie� eventy dla wci�ni�tego raz klawisza myszy
{
	if (Mouse::pressedOnce(Mouse_key::L_BUTTON))
		on_mouseL1hit();
	else if (Mouse::pressedOnce(Mouse_key::R_BUTTON))
		on_mouseR1hit();
	else if (Mouse::pressedOnce(Mouse_key::MID_BUTTON))
		on_mouseW1hit();

	/*switch (mouse_key) {
	case Mouse_key::L_BUTTON:
		on_mouseL1hit();
		break;
	case Mouse_key::R_BUTTON:
		on_mouseR1hit();
		break;
	case Mouse_key::MID_BUTTON:
		on_mouseW1hit();
		break;
	}*/
}

void Object::keyboardEvents_1hit()
{

}

void Object::mouse_handler()
{
	mouse_key = Mouse::getBt_state();

	if (mouse_key != Mouse_key::NONE)
		mouseEvents_1hit();
}

void Object::keyboard_handler()
{
	if (!Keyboard::is_pressedKey_once(Key::NONE))
		keyboardEvents_1hit();
}
