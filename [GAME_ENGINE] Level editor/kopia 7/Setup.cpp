#include "Setup.h"
#include "Exceptions.h"

SDL_Renderer * Setup::renderer = nullptr;
SDL_Window * Setup::window = nullptr;
SDL_Event Setup::events = {};
SDL_DisplayMode Setup::displayMode = {};
int Setup::windowW{};
int Setup::windowH{};

void Setup::init(int & w, int & h)
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
	w = displayMode.w / 1280;
	h = displayMode.h / 1024;

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
