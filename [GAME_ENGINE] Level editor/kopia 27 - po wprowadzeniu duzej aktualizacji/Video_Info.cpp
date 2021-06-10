#include "Video_Info.h"

SDL_DisplayMode Video_Info::display_mode{};

double Video_Info::scaleW{};
double Video_Info::scaleH{};

bool Video_Info::fullscreen{ false };

int Video_Info::window_H{};
int Video_Info::window_W{};

void Video_Info::Init()
{
	SDL_GetDesktopDisplayMode(0, &display_mode);
	set_windowed();
}

void Video_Info::set_fullscreen()
{
	window_W = display_mode.w;
	window_H = display_mode.h;

	scaleH = double(display_mode.h) / double(1024);
	scaleW = double(display_mode.w) / double(1280);

	fullscreen = true;
}

void Video_Info::set_windowed()
{
	window_W = display_mode.w - 100;
	window_H = display_mode.h - 100;

	scaleH = double(window_H) / double(924);
	scaleW = double(window_W) / double(1180);

	fullscreen = false;
}