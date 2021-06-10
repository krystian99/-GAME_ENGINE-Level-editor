#include <SDL.h>
#include "Setup.h"
#include "Video_Info.h"
#include "Renderer.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Enemy_Types.h"
#include "Folder_button.h"

Setup::Setup() // inicjuje wszystkie zasoby
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();

	Video_Info::Init();
	Renderer::Init();
	//Keyboard::Init();

	using namespace Enemy_Types;

	Folder_button::set_Texture("data/engine_files/test.png");

	Enemy_Test::setTexture("data/textures/test.png");
	Enemy_Test2::setTexture("data/textures/test2.png");
	Enemy_Test3::setTexture("data/textures/test3.png");
	Enemy_Test4::setTexture("data/textures/test4.png");
}

Setup::~Setup()
{
	Renderer::Destroy();
}