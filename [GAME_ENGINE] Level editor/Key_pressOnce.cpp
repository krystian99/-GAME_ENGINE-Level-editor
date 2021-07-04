#include "Key_pressOnce.h"
#include "Mouse.h"

Key_pressOnce::Key_pressOnce(const std::vector<Mouse_key>& keys) :
	mouse_keys{ Mouse::getKeys() }
{
	this->keys = std::move(keys);
}

void Key_pressOnce::events()
{
	reset();

	if (isPressed()) {
		pressed = true;
		++count;

		if (count > 1)
			pressed_once = false;
		else
			pressed_once = true;
	}
	else if (!pressed)
		count = 0;
}

bool Key_pressOnce::pressedOnce()
{
	return pressed_once;
}

void Key_pressOnce::reset()
{
	pressed = false;
}

bool Key_pressOnce::isPressed() const
{
	for (auto& i : keys)
		if (!mouse_keys[int(i)])
			return false;

	return true;
}
