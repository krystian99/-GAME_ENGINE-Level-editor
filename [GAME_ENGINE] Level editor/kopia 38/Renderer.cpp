#include "Renderer.h"
#include "Video_Info.h"
#include "Error.h"

SDL_Renderer * Renderer::renderer{};
SDL_Window * Renderer::window{};

int Renderer::window_ID{};

void Renderer::Init()
{
	if (!(window = SDL_CreateWindow("Level Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Video_Info::getWindow_W(), Video_Info::getWindow_H(), SDL_WINDOW_SHOWN)))
		throw Error::throw_Message("Couldn't create window!: " + std::string{ SDL_GetError() });
	if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		throw Error::throw_Message("Renderer couldn't be loaded!: " + std::string{ SDL_GetError() });
	window_ID = SDL_GetWindowID(window);
	clear();
	update();
}

void Renderer::set_renderColor(const SDL_Color & color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Renderer::set_defaultColor()
{
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
}

void Renderer::clear()
{
	set_defaultColor();
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