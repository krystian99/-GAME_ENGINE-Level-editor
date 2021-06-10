#pragma once
#include <SDL_video.h>

class Video_Info
{
public:
	static void Init();

	static bool is_fullscreen() { return fullscreen; }

	static const double & get_scaleW() { return scaleW; }
	static const double & get_scaleH() { return scaleH; }

	static const int & getWindow_W() { return window_W; }
	static const int & getWindow_H() { return window_H; }

	static void set_fullscreen();
	static void set_windowed();

	static const SDL_DisplayMode & getInfo() { return display_mode; }
private:
	static double scaleW, scaleH; // zmienia siê zale¿nie od stanu fullscreen = false, true

	static int window_H, window_W;

	static bool fullscreen;

	static SDL_DisplayMode display_mode;
};