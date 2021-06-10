#include "Setup.h"
#include "Exceptions.h"

SDL_Renderer * Setup::renderer = nullptr;
SDL_Window * Setup::window = nullptr;
SDL_Event Setup::events = {};
SDL_DisplayMode Setup::displayMode = {};
int Setup::windowW{};
int Setup::windowH{};

void Setup::init(double & scaleW, double & scaleH)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		throw Error{ SDL_GetError() };
	SDL_GetDesktopDisplayMode(0, &displayMode);
	if (!(window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, displayMode.w /*- 100*/, displayMode.h /*- 100*/, SDL_WINDOW_SHOWN))) // wersja poprzednia (usuniête -100)
		throw Error{ SDL_GetError() };
	else if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		throw Error{ SDL_GetError() };
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw Error{ SDL_GetError() };
	if (TTF_Init() != 0)
		throw Error{ SDL_GetError() };
	scaleW = double(displayMode.w) / double(1280);
	scaleH = double(displayMode.h) / double(1024);

	SDL_GetWindowSize(window, &windowW, &windowH);
}


void Setup::DestroyAll()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
}

void Setup::PollEvents()
{
	while (!SDL_PollEvent(&events)) { 
		SDL_Delay(1);
		continue;
	}
}

void Setup::PollEvent(SDL_EventType event_type)
{
	/*while (events.type != event_type) {
		if (event_type == events.type)
			break;
		SDL_Delay(1);
		continue;
	}*/
	while (SDL_WaitEvent(&events) >= 0) {
		/*if (event_type == events.type) {
			SDL_PollEvent(&events);
			break;
		}*/
		SDL_Delay(1);
		break;
	}
}
