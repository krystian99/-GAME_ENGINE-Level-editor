#include "Key_pressOnce_s.h"
#include "Keyboard.h"
#include <algorithm>

void Key_pressOnce_s::events()
{
	if (!keys_pressonce.empty()) {
		for (auto& key_pressed : keys_pressonce)
		{
			if (!key_pressed.is_flagActivated())
			{
				key_pressed.set_flag(true);
				key_pressed.set_pressedOnce(true);
			}
			else
				key_pressed.set_pressedOnce(false);
		}
	}
}

bool Key_pressOnce_s::is_pressedOnce(Key key)
{
	if (!keys_pressonce.empty()) {
		if (keys_pressonce.size() > 1)
			return false;
		else {
			auto& key_pressed = keys_pressonce.front();

			if (key_pressed.compare_key(key))
				return key_pressed.is_pressedOnce();
		}
	}

	return false;
}

bool Key_pressOnce_s::is_pressedOnce(std::vector<Key> keys)
{
	if (keys_pressonce.size() < keys.size())
		return false;

	std::sort(keys.begin(), keys.end(), [](Key k1, Key k2)
		{ return int(k1) < int(k2); }
	);

	for (int i = 0; i < keys_pressonce.size(); ++i) {
		auto& key_pressed = keys_pressonce[i];
		auto& key_check = keys[i];

		if (!key_pressed.compare_key(key_check) || !key_pressed.is_pressedOnce())
			return false;
	}

	return true;
}

// dodaj nowy przycisk klikniety
void Key_pressOnce_s::switch_keysDown(const Key& code)
{
	// wyzeruj flagi by w nastepnym przebiegu oba klawisze nie byly klikniête
	for (auto& k : keys_pressonce)
		k.reset();

	keys_pressonce.push_back({ code });

	if (keys_pressonce.size() > 1) {
		std::sort(keys_pressonce.begin(), keys_pressonce.end(), [](const key_pressOnce& k1, const key_pressOnce& k2)
			{ return k1.getKey() < k2.getKey(); }
		);
	}
}

void Key_pressOnce_s::switch_keysUp(const Key& code)
{
	for (int i = 0; i < keys_pressonce.size(); ++i)
	{
		auto& key_up = keys_pressonce[i];

		auto k = key_up.getKey();


		if (key_up.compare_key(code))
		{
			std::swap(key_up, keys_pressonce.back());
			keys_pressonce.pop_back();
			break;
		}
	}
}

void Key_pressOnce_s::key_pressOnce::reset()
{
	pressed_once = false;
	flag_pressed_once = false;
}
