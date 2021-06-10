#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Setup
{
public:
	static void init();

	static void DestroyAll();

	static void PollEvents();

	static const SDL_DisplayMode * getDspMode() { return &displayMode; }

	static int getDisplayWidth() { return displayMode.w; }

	static int getDisplayHeight() { return displayMode.h; }

	static SDL_Event * getEvent() { return &events; }

	static SDL_Renderer * getRenderer() { return renderer; }

	static int getRefreshRate() { return displayMode.refresh_rate; }
private:
	static SDL_DisplayMode displayMode;
	static SDL_Renderer * renderer;
	static SDL_Window * window;
	static SDL_Event events;
};

