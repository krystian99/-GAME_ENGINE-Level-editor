#include "Object.h"

void Object::events()
{
	if (Mouse::getX() >= position.x && Mouse::getX() <= position.x + position.w
		&& Mouse::getY() >= position.y && Mouse::getY() <= position.y + position.h)
	{
		mouse_over = true;
	}
	else
		mouse_over = false;

	if (is_mouseOver()) {
		mouse_handler();
		keyboard_handler();
	}
}

void Object::update_position(int renderX, int renderY)
{
	position.x = renderX;
	position.y = renderY;
}

void Object::set_position(SDL_Rect pos)
{
	this->position = pos;
}

void Object::reset_states()
{
	mouse_key = Mouse_key::NONE;
	keyboard_key = Key::NONE;
}

void Object::mouseEvents_1hit() // jakie� eventy dla wci�ni�tego raz klawisza myszy
{
	switch (mouse_key) {
	case Mouse_key::L_BUTTON:
		break;
	case Mouse_key::R_BUTTON:
		break;
	case Mouse_key::MID_BUTTON:
		break;
	}
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
	keyboard_key = Keyboard::getState();

	if (keyboard_key != Key::NONE)
		keyboardEvents_1hit();
}