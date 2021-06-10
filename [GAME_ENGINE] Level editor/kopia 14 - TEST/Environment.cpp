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
		//if (Keyboard::getState() == Key::ESCAPE)
			//return;
		while (SDL_PollEvent(Setup::getEvent()) != 0) { // v3
			SDL_RenderClear(Setup::getRenderer());

			if (Keyboard::getState() == Key::ESCAPE)
				return;

			Mouse::update(Setup::getEvent());
			Keyboard::events(Setup::getEvent());

			switch_AppState();
			SDL_RenderPresent(Setup::getRenderer());

			SDL_Delay(1);
			continue;
		}
	}
}

void Environment::events() {
	while (SDL_PollEvent(Setup::getEvent()) != 0) { // v3
		SDL_RenderClear(Setup::getRenderer());

		Mouse::update(Setup::getEvent());
		Keyboard::events(Setup::getEvent());

		switch_AppState();
		SDL_RenderPresent(Setup::getRenderer());

		SDL_Delay(1);
	}

	/*while (SDL_PollEvent(Setup::getEvent()) != 0) { // v2
		SDL_RenderClear(Setup::getRenderer());

		Mouse::update(Setup::getEvent());
		Keyboard::events(Setup::getEvent());

		switch_AppState();
		SDL_RenderPresent(Setup::getRenderer());
		SDL_Delay(1);
	}*/
	/*SDL_RenderClear(Setup::getRenderer()); // v1

	Mouse::update(Setup::getEvent());
	Keyboard::events(Setup::getEvent());

	switch_AppState();
	SDL_RenderPresent(Setup::getRenderer());
	SDL_Delay(1);*/
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