#pragma once
#include <vector>

enum class Mouse_key;

class Key_pressOnce
{
public:
	Key_pressOnce(const std::vector<Mouse_key>& keys);

	void events();

	bool pressedOnce();

	bool isPressed() const;

	int getCode() const { return code; }

	void reset();
private:
	bool pressed{ false };

	//int count{ 0 };

	int code;

	//int* counts;

	std::vector<Mouse_key> check_keys;

	bool flag_pressed_once{ false };
	//bool pressed_once{ false };

	const bool* mouse_keys;
	bool* pressed_once;
};

