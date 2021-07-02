#include "Key_pressOnce.h"
#include "Mouse.h"

Key_pressOnce::Key_pressOnce(const std::vector<Mouse_key>& keys) :
	mouse_keys{ Mouse::getKEYS() }
{
	this->keys = std::move(keys);
}

void Key_pressOnce::events()
{
	pressed = false;

	if (isPressed())
		pressed = true;
}

bool Key_pressOnce::pressedOnce()
{
	if (!flag_pressed_once && pressed)
	{
		pressed_once = true;
		flag_pressed_once = true;

	}
	else if (flag_pressed_once)
	{
		pressed_once = false;

		if (!pressed)
			flag_pressed_once = false;
	}

	return pressed_once;
}

void Key_pressOnce::reset()
{

}

bool Key_pressOnce::isPressed() const
{
	for (auto& i : keys)
		if (!mouse_keys[int(i)])
			return false;

	return true;
}
