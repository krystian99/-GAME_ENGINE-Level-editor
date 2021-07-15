#pragma once
#include <SDL_events.h>
#include <vector>

enum class  Key;

// s- structure
class Key_pressOnce_s
{
public:
	bool is_pressedOnce(Key key);
	bool is_pressedOnce(std::vector<Key> keys);

	void events();

	void switch_keysDown(const Key& code);
	void switch_keysUp(const Key& code);
private:
	class key_pressOnce
	{
	public:
		key_pressOnce(Key key) { this->key = key; }

		Key getKey() const { return key; }

		void reset();

		bool compare_key(Key k) const { return key == k; }

		void setKey(Key key) { this->key = key; }
		void set_pressedOnce(bool var) { pressed_once = var; }
		void set_flag(bool var) { flag_pressed_once = var; }

		bool is_flagActivated() const { return flag_pressed_once; }
		bool is_pressedOnce() const { return pressed_once; }
	private:
		Key key;
		bool pressed_once{ false };
		bool flag_pressed_once{ false };
	};

	std::vector<key_pressOnce> keys_pressonce;
};
