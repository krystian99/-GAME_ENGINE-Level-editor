#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Setup
{
public:
	static void init(double & scaleW, double & scaleH);

	static void DestroyAll();

	static void PollEvents(); // usu� wszystkie zdarzenia z kolejki zdarze�
	static void PollEvent(SDL_EventType event_type); // czeka a� element zostanie usuni�ty z kolejki zdarze�

	static const SDL_DisplayMode * getDspMode() { return &displayMode; }

	static int getDisplayWidth() { return displayMode.w; }

	static int getDisplayHeight() { return displayMode.h; }

	static SDL_Event * getEvent() { return &events; }

	static SDL_Renderer * getRenderer() { return renderer; }

	static int getRefreshRate() { return displayMode.refresh_rate; }
private:
	static int windowH, windowW;

	static SDL_DisplayMode displayMode;
	static SDL_Renderer * renderer;
	static SDL_Window * window;
	static SDL_Event events;
};

