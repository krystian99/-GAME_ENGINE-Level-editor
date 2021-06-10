#include "Environment.h"
#include "Setup.h"
#include "Mouse.h"

Environment::Environment() :
	sbStatic{ ButtonType::STATIC, SB_Orientation::VERTICAL },
	sbDynamic{ ButtonType::DYNAMIC, SB_Orientation::VERTICAL },
	sbKey{ ButtonType::KEY, SB_Orientation::HORIZONTAL }
{
	Init();
	sbStatic.Init({ 0, 100, 100, Setup::getDisplayHeight() - 200 });
	sbDynamic.Init({ Setup::getDisplayWidth() - 100, 100, 100, Setup::getDisplayHeight() - 200 });
	sbKey.Init({ 100 , 0, Setup::getDisplayWidth() - 200, 100 });
	start_render();
}

void Environment::run()
{
	for (;;) {
		switchAppState();

		Setup::PollEvents(); // usuwa elementy z kolejki zdarzeñ

		Mouse::update(Setup::getEvent());
		if (Setup::getEvent()->type == SDL_QUIT)
			return;
		else if (Setup::getEvent()->type == SDL_KEYUP)
			if (Setup::getEvent()->key.keysym.sym == SDLK_ESCAPE)
				return;
		renderAll();
		SDL_Delay(1);
	}
}

void Environment::events() {
	sbDynamic.events(Setup::getEvent());
	sbKey.events(Setup::getEvent());
	sbStatic.events(Setup::getEvent());
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

void Environment::renderAll()
{
	SDL_RenderClear(Setup::getRenderer());
	sbDynamic.render(Setup::getRenderer());
	sbStatic.render(Setup::getRenderer());
	sbKey.render(Setup::getRenderer());
	SDL_RenderPresent(Setup::getRenderer());
}

void Environment::switchAppState()
{
	switch (state)
	{
	case Event_state::NONE:
		events();
		break;
	case Event_state::BUTTON_CLICKED:
		break;
	}
}

