#include <SDL.h>
#include "Setup.h"
#include "Video_Info.h"
#include "Renderer.h"
#include "Enemy_Test.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

Setup::Setup() // inicjuje wszystkie zasoby
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();

	Video_Info::Init();
	Renderer::Init();
	Enemy_Test::setTexture("data/textures/test.png");
}

Setup::~Setup()
{
	Renderer::Destroy();
}