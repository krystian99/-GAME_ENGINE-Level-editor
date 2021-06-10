#include "Environment.h"
#include "Setup.h"
#include "Mouse.h"
#include "Keyboard.h"

Environment::Environment() :
	state{ APP_state::IS_IN_MENU },
	menu{ state },
	Level_Environment{}
{
	Init();
	menu.setMenus(Setup::getDspMode());
	Level_Environment.Init(Setup::getDspMode(), scaleW, scaleH);
}

void Environment::run()
{
	for (;;) {
		events();
		if (Setup::getEvent()->type == SDL_QUIT)
			return;
		else if (Setup::getEvent()->type == SDL_KEYUP)
			if (Setup::getEvent()->key.keysym.sym == SDLK_ESCAPE)
				return;
		//Setup::PollEvents();
		SDL_PollEvent(Setup::getEvent());
		SDL_Delay(1);
	}
}

void Environment::events() {
	SDL_RenderClear(Setup::getRenderer());

	Mouse::update(Setup::getEvent());
	Keyboard::events(Setup::getEvent());

	switch_AppState();
	SDL_RenderPresent(Setup::getRenderer());
	SDL_Delay(1);
}
Environment::~Environment()
{
	Setup::DestroyAll();
}

void Environment::Init()
{
	Setup::init(scaleW, scaleH);
	start_render();
}

void Environment::start_render()
{
	SDL_SetRenderDrawColor(Setup::getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(Setup::getRenderer());
	SDL_RenderPresent(Setup::getRenderer());
}

void Environment::switch_AppState()
{
	switch (state)
	{
	case APP_state::IS_IN_MENU:
		menu.events(Setup::getRenderer());
		break;
	case APP_state::IS_IN_LC:
		Level_Environment.events(Setup::getRenderer());
		break;
	case APP_state::IS_IN_MC:
		break;
	}
}