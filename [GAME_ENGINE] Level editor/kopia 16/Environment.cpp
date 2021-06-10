#include "Environment.h"
#include "Setup.h"
#include "Mouse.h"
#include "Keyboard.h"

Environment::Environment() :
	state{ APP_state::IS_IN_MENU },
	menu{ state },
	Level_Environment{},
	running{ true }
{
	Init();
	menu.setMenus(Setup::getDspMode());
	Level_Environment.Init(Setup::getDspMode(), scaleW, scaleH);
}

void Environment::run()
{
	while (running) {
		events();
		SDL_Delay(1);
	}
}

void Environment::events() {
	while (SDL_PollEvent(Setup::getEvent()) != 0) // v3 - trzeba podzieliæ osobno renderowanie i zdarzenia
	{
		Mouse::update(Setup::getEvent());
		Keyboard::events(Setup::getEvent());

		if (Keyboard::getState() == Key::ESCAPE) {
			running = false;
			return;
		}

		switch_AppState_Events();

		SDL_Delay(1);
		continue;
	}
	switch_AppState_Render();
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

void Environment::switch_AppState_Events()
{
	switch (state)
	{
	case APP_state::IS_IN_MENU:
		menu.events();
		break;
	case APP_state::IS_IN_LC:
		Level_Environment.events();
		break;
	case APP_state::IS_IN_MC:
		break;
	}
}

void Environment::switch_AppState_Render()
{
	SDL_RenderClear(Setup::getRenderer());
	switch (state)
	{
	case APP_state::IS_IN_MENU:
		menu.events_independent();
		menu.render(Setup::getRenderer());
		break;
	case APP_state::IS_IN_LC:
		Level_Environment.render(Setup::getRenderer());
		break;
	case APP_state::IS_IN_MC:
		break;
	}
	SDL_RenderPresent(Setup::getRenderer());
}