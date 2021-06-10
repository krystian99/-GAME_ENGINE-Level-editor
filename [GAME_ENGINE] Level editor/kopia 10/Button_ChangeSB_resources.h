#pragma once
#include <string>
#include <SDL_render.h>

namespace Button_ChangeSB_resources {
	using std::string;

	const string TTF_path = "files/lazy.ttf";
	const int TTF_size = 60;
	const SDL_Color TTF_color = { 0, 0, 255, 255 };

	const string Dynamic_backgroundTX = "files/ButtonsChangeSB/DynamicBG.png";
	const string Static_backgroundTX = "files/ButtonsChangeSB/StaticBG.png";
	const string Key_backgroundTX = "files/ButtonsChangeSB/KeyBG.png";
}