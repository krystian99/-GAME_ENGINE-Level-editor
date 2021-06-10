#include "Environment.h"
#include "Setup.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Renderer.h"

Environment::Environment() :
	state{ APP_state::IS_IN_MENU },
	Level_Environment{},
	running{ true }
{
	menu.Init();
	Level_Environment.Init();
}

void Environment::run()
{
	while (running) {
		events();
		render();
	}
}

void Environment::events() {

	static const Uint8 * keyboard = SDL_GetKeyboardState(nullptr);

	while (SDL_PollEvent(&event_handler))
	{
		Mouse::update();

		if (keyboard[SDL_SCANCODE_ESCAPE] || event_handler.type == SDL_QUIT) {
			running = false;
			return;
		}

		switch (state)
		{
		case APP_state::IS_IN_MENU:
			menu.events();
			switch (menu.getState()) {
			case MENU_STATE::CREATING_LEVEL:
				Level_Environment.new_Level(menu.getInput());
				break;
			case MENU_STATE::LOAD_LEVEL:
				if (!Level_Environment.load_Level(menu.getInput()))
					menu.setRecentlyState();
				break;
			}
			break;
		case APP_state::IS_IN_LC:
			Level_Environment.events();
			break;
		}

		SDL_Delay(1);
	}
}

void Environment::render()
{
	Renderer::clear();
	switch (state)
	{
	case APP_state::IS_IN_MENU:
		menu.events_independent();
		menu.render();
		break;
	case APP_state::IS_IN_LC:
		Level_Environment.render();
		break;
	}
	Renderer::update();
}