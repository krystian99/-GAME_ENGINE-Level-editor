#pragma once
#include <SDL_render.h>
#include <SDL_events.h>

class SDL_Setup
{
public:
	SDL_Setup();
	~SDL_Setup();
private:
	SDL_Event ev;
	SDL_Renderer * renderer;
	SDL_Window * window;
};

