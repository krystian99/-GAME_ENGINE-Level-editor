#include "Environment.h"
#include "Setup.h"
#include "Mouse.h"
#include "Renderer.h"
#include "Engine_manager.h"
#include "Keyboard.h"
#include "LevelEditor_manager.h"

// TEST
//unsigned long long Environment::ev_counter{ 0 };
//unsigned long long Environment::ev_idnp_counter{ 0 };
// END TEST


void Environment::run()
{
	while (Engine_manager::is_running()) {
		events();
		render();
	}
}

void Environment::events() 
{
	while (SDL_PollEvent(&event_handler)) // zdarzenia zale�ne od aktualizacji 
	{
		//ev_counter++;
		if (event_handler.type == SDL_QUIT) {
			Engine_manager::Quit();
			break;
		}
		Keyboard::events(&event_handler);
		Mouse::update(&event_handler);
		events_dpnd();
	}
	events_indp();
}

void Environment::events_indp()
{
	//ev_idnp_counter++;
	static const Uint8 * key = SDL_GetKeyboardState(nullptr);
	if (!escape_pressed && !test) {
		if (key[SDL_SCANCODE_ESCAPE])
			escape_pressed = true;
	}

	if (escape_pressed && Engine_manager::getState() == Engine_state::IS_IN_LC)
	{
		escape_pressed = false;

		Engine_manager::setState(Engine_state::IS_IN_MENU);
		Menu_manager::set_Menu(Menu_ID::START);
	}

	if (key[SDL_SCANCODE_ESCAPE]) {
		test = true;
		escape_pressed = false;
	}
	else if (!key[SDL_SCANCODE_ESCAPE])
		test = false;

	switch (Engine_manager::getState())
	{
	case Engine_state::IS_IN_MENU:
		menu.events_indp();
		break;
	case Engine_state::IS_IN_LC:
		level_editor.events_indp();
		break;
	}
}

void Environment::events_dpnd()
{
	switch (Engine_manager::getState())
	{
	case Engine_state::IS_IN_MENU:
		menu.events();
		break;
	case Engine_state::IS_IN_LC:
		level_editor.events();
		break;
	}
}

void Environment::render()
{
	Renderer::clear();
	switch (Engine_manager::getState())
	{
	case Engine_state::IS_IN_MENU:
		menu.render();
		break;
	case Engine_state::IS_IN_LC:
		level_editor.render();
		break;
	}
	Renderer::update();
}