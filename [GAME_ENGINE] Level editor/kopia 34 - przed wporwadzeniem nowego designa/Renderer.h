#pragma once
#include <SDL_render.h>

class Renderer
{
public:
	static void Init();

	static SDL_Renderer * get() { return renderer; }

	static void set_renderColor(const SDL_Color & color);
	static void set_defaultColor();

	static void clear();

	static void update();

	static void Destroy();
private:
	static SDL_Renderer * renderer;
	static SDL_Window * window;
};

