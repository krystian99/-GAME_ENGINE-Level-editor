#pragma once
#include "Mouse.h"
#include <vector>

class Key_pressOnce
{
public:
	Key_pressOnce(const std::vector<Mouse_key>& keys, const bool* mouse_ks);

	void events();

	bool is_pressed() const { return pressed; }

	bool pressedOnce();

	void reset();
private:
	bool isPressed() const;
private:
	bool pressed{ false };

	int count{ 0 };

	std::vector<Mouse_key> keys;

	bool flag_pressed_once{ false };
	bool pressed_once{ false };

	const bool* mouse_keys;
};