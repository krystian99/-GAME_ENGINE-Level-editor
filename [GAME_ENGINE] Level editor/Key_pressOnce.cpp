#include "Key_pressOnce.h"
#include "Mouse.h"
#include <iostream>

Key_pressOnce::Key_pressOnce(const std::vector<Mouse_key>& keys)
{
	check_keys = keys;

	mouse_keys = Mouse::getKeys();

	//counts = Mouse::getCounts();

	pressed_once = Mouse::get_pressedOnce();

	for (auto& i : keys)
	{
		code |= int(i);
	}
}

void Key_pressOnce::events()
{
	reset();

	if (isPressed()) {
		pressed = true;

		if (!flag_pressed_once) {
			flag_pressed_once = true;

			pressed_once[code] = true;
		}
	}
	else
		flag_pressed_once = false;
}

bool Key_pressOnce::pressedOnce()
{
	return pressed_once[code];
}

void Key_pressOnce::reset()
{
	pressed = false;
	pressed_once[code] = false;
}

bool Key_pressOnce::isPressed() const
{
	for (auto& i : check_keys)
		if (!mouse_keys[int(i)])
			return false;

	return true;
}
