#include "Environment.h"
#include "Setup.h"
#include "Mouse.h"

Environment::Environment()
{
	Init();
	menu.setMenus(Setup::getDspMode());
	start_render();
}

void Environment::run()
{
	for (;;) {
		events();

		SDL_Delay(1);
	}
}

void Environment::events() {
	Setup::PollEvents(); // usuwa elementy z kolejki zdarzeñ

	if (Setup::getEvent()->type == SDL_QUIT)
		return;
	else if (Setup::getEvent()->type == SDL_KEYUP)
		if (Setup::getEvent()->key.keysym.sym == SDLK_ESCAPE)
			return;

	Mouse::update(Setup::getEvent());

	switch_AppState();
}
Environment::~Environment()
{
	Setup::DestroyAll();
}

void Environment::Init()
{
	Setup::init();
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
		switch_LevelCreatorState();
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
		menu.run_Start(state, Setup::getRenderer());
		break;
	case MENU_STATE::LC_MENU:
		menu.run_LC(state, Setup::getRenderer());
		break;
	case MENU_STATE::MC_MENU:
		menu.run_MC(state, Setup::getRenderer());
		break;
	case MENU_STATE::PAUSE_MENU:
		menu.run_Paused(state, Setup::getRenderer());
		break;
	}
}

void Environment::switch_LevelCreatorState()
{

}

void Environment::switch_MenuCreatorState()
{

}

