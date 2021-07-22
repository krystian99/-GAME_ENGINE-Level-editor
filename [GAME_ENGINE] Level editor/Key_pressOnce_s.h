#pragma once
#include <SDL_events.h>
#include <vector>
#include <algorithm>

// s- structure
template <typename T>
class Key_pressOnce_s
{
	class key_pressOnce
	{
	public:
		key_pressOnce(T key) { this->key = key; }

		T getKey() const { return key; }

		void reset();

		bool compare_key(T k) const { return key == k; }

		void setKey(T key) { this->key = key; }
		void set_pressedOnce(bool var) { pressed_once = var; }
		void set_flag(bool var) { flag_pressed_once = var; }

		bool is_flagActivated() const { return flag_pressed_once; }
		bool is_pressedOnce() const { return pressed_once; }
	private:
		T key;
		bool pressed_once{ false };
		bool flag_pressed_once{ false };
	};
public:
	bool is_pressedOnce(T key);
	bool is_pressedOnce(std::vector<T> keys);

	bool empty() const { return keys_pressonce.empty(); }

	bool is_1keyPressed() const { return keys_pressonce.size() == 1; }

	T get_pressed1_key() const;

	const std::vector<key_pressOnce>& get_pressedKeys() const { return keys_pressonce; }

	void events();

	void switch_keysDown(const T& code);
	void switch_keysUp(const T& code);
private:
	std::vector<key_pressOnce> keys_pressonce;
};

template<typename T>
T Key_pressOnce_s<T>::get_pressed1_key() const
{
	if (keys_pressonce.size() == 1)
	{
		const key_pressOnce & pressed_key = keys_pressonce.front();

		if (pressed_key.is_pressedOnce())
			return pressed_key.getKey();
	}

	return T::NONE;
}

template<typename T>
void Key_pressOnce_s<T>::events()
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

template<typename T>
bool Key_pressOnce_s<T>::is_pressedOnce(T key)
{
	if (!keys_pressonce.empty()) {
		if (keys_pressonce.size() > 1)
			return false;

		auto& key_pressed = keys_pressonce.front();

		if (key_pressed.compare_key(key))
			return key_pressed.is_pressedOnce();
	}

	return false;
}

template<typename T>
bool Key_pressOnce_s<T>::is_pressedOnce(std::vector<T> keys)
{
	if (keys_pressonce.empty() || keys_pressonce.size() < keys.size())
		return false;

	std::sort(keys.begin(), keys.end(), [](T k1, T k2)
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
template<typename T>
void Key_pressOnce_s<T>::switch_keysDown(const T& code)
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
template<typename T>
void Key_pressOnce_s<T>::switch_keysUp(const T& code)
{
	for (auto & key_up : keys_pressonce)
	{
		if (key_up.compare_key(code))
		{
			std::swap(key_up, keys_pressonce.back());
			keys_pressonce.pop_back();
			break;
		}
	}
}

template<typename T>
void Key_pressOnce_s<T>::key_pressOnce::reset()
{
	pressed_once = false;
	flag_pressed_once = false;
}
