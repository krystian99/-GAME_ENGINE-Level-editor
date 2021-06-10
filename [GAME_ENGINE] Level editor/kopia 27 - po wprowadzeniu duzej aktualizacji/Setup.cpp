#include <SDL.h>
#include "Setup.h"
#include "Video_Info.h"
#include "Renderer.h"

Setup::Setup()
{
	SDL_Init(SDL_INIT_VIDEO);

	Video_Info::Init();
	Renderer::Init();
}

Setup::~Setup()
{
	Renderer::Destroy();
}