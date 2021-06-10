#pragma once
#include <SDL_render.h>

class Renderer
{
public:
	static void Init();

	static SDL_Renderer * get() { return renderer; }

	static void clear();

	static void update();

	static void Destroy();
private:
	static SDL_Renderer * renderer;
	static SDL_Window * window;
};

