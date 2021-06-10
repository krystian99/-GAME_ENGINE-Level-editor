#include "Environment.h"
#include "Setup.h"
#include "Mouse.h"
#include "Keyboard.h"

Environment::Environment() :
	state{ APP_state::IS_IN_MENU },
	recent{ APP_state::IS_IN_MENU },
	menu{ state, recent },
	Level_Environment{},
	running{ true }
{
	Init();
	menu.Init(Setup::getDspMode(), scaleW, scaleH);
	Level_Environment.Init(Setup::getDspMode(), scaleW, scaleH);
}

void Environment::run()
{
	while (running) {
		events();
		render();
		SDL_Delay(1);
	}
}

void Environment::events() {
	while (SDL_PollEvent(Setup::getEvent()))
	{
		Mouse::update(Setup::getEvent());
		Keyboard::events(Setup::getEvent());

		if (Keyboard::getState() == Key::ESCAPE) {
			running = false;
			return;
		}

		switch (state)
		{
		case APP_state::IS_IN_MENU:
			menu.events();
			switch (menu.getState()) {
			case MENU_STATE::CREATING_LEVEL:
				Level_Environment.newLevel(menu.getInput());
				break;
			case MENU_STATE::LOAD_LEVEL:
				if (!Level_Environment.loadLevel(menu.getInput()))
					menu.setRecentlyState();
				break;
			}
			break;
		case APP_state::IS_IN_LC:
			Level_Environment.events(Setup::getRenderer());
			break;
		}

		SDL_Delay(1);
	}
}

void Environment::render()
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
	}
	SDL_RenderPresent(Setup::getRenderer());
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