#pragma once
#include <vector>
#include "Mouse_keys.h"

class Key_pressOnce
{
public:
	Key_pressOnce(const std::vector<Mouse_key>& keys);

	void events();

	bool is_pressed() const { return pressed; }

	bool pressedOnce();

	void reset();
private:
	bool isPressed() const;
private:
	bool pressed{ false };

	std::vector<Mouse_key> keys;

	bool flag_pressed_once{ false };
	bool pressed_once{ false };

	const bool* mouse_keys;
};