#include "Object.h"
#include "Video_Info.h"

Object::Object(Rect render_position)
	: Rect{ render_position }
{

}

Object::Object(int x, int y, int w, int h)
{
	set_position(x, y, w, h);
}

void Object::events()
{
	if (Mouse::is_inPOS(get_position()))
	{
		//reset_states();

		mouse_over = true;

		on_mouseOver();

		//mouseEvents_1hit();

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

}

void Object::mouse_handler()
{
	if (Mouse::is_pressedL_once())
		on_mouseL1hit();
	else if (Mouse::pressedOnce(Mouse_key::R_BUTTON))
		on_mouseR1hit();
	else if (Mouse::pressedOnce(Mouse_key::MID_BUTTON))
		on_mouseW1hit();
}

void Object::keyboard_handler()
{
	if (!Keyboard::is_pressedKey_once(Key::NONE))
		keyboardEvents_1hit();
}
