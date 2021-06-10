#include "Environment.h"
#include "Setup.h"
#include "Mouse.h"

Environment::Environment() :
	state{ APP_state::IS_IN_MENU },
	menu{ state },
	Level_Environment{}
{
	Init();
	menu.setMenus(Setup::getDspMode());
	Level_Environment.Init(Setup::getDspMode(), scaleW, scaleH);
	//start_render();
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
		SDL_PollEvent(Setup::getEvent());
		SDL_Delay(1);
	}
}

void Environment::events() {
	SDL_RenderClear(Setup::getRenderer());

	Mouse::update(Setup::getEvent());

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
		switch_menuState();
		break;
	case APP_state::IS_IN_LC:
		Level_Environment.events(Setup::getRenderer());
		break;
	case APP_state::IS_IN_MC:
		switch_MenuCreatorState();
		break;
	}
}

void Environment::switch_menuState()
{
	switch (menu.getMenuState())
	{
	case MENU_STATE::START_MENU:
		menu.run_Start(Setup::getRenderer());
		break;
	case MENU_STATE::LC_MENU:
		menu.run_LC(Setup::getRenderer());
		break;
	case MENU_STATE::MC_MENU:
		menu.run_MC(Setup::getRenderer());
		break;
	case MENU_STATE::PAUSE_MENU:
		menu.run_Paused(Setup::getRenderer());
		break;
	}
}

void Environment::switch_LevelCreatorState()
{

}

void Environment::switch_MenuCreatorState()
{

}

