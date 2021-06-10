#include "Renderer.h"
#include "Video_Info.h"
#include "Error.h"

SDL_Renderer * Renderer::renderer{};
SDL_Window * Renderer::window{};

void Renderer::Init()
{
	if (!(window = SDL_CreateWindow("Level Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Video_Info::getWindow_W(), Video_Info::getWindow_H(), SDL_WINDOW_SHOWN)))
		throw Error::throw_Message("Couldn't create window!: " + std::string{ SDL_GetError() });
	if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		throw Error::throw_Message("Renderer couldn't be loaded!: " + std::string{ SDL_GetError() });
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Renderer::clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::update()
{
	SDL_RenderPresent(renderer);
}

void Renderer::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}