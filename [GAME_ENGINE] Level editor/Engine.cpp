#include "Engine.h"
#include "Engine_manager.h"
#include "Menu_manager.h"
#include "LevelEditor_manager.h"
#include "Mouse.h"
#include "Renderer.h"
#include "Keyboard.h"
#include "Event_handler.h"

Engine::Engine()
{
	Engine_manager::INIT(&menu, &level_editor, &animation_config_creator, &script_editor);
}

void Engine::run()
{
	while (Engine_manager::is_running()) {
		events();
		render();
	}
}

void Engine::events()
{
	while (SDL_PollEvent(&event_handler)) // zdarzenia zale¿ne od aktualizacji 
	{
		Keyboard::events(&event_handler);
		Mouse::update(&event_handler);

		if (event_handler.type == SDL_WINDOWEVENT && event_handler.window.windowID == Renderer::get_mainWindow_ID()) {
			switch (event_handler.window.event) {
			case SDL_WINDOWEVENT_CLOSE:
				Engine_manager::Quit();
				break;
			}
		}

		if (event_handler.window.windowID == Renderer::get_mainWindow_ID())
			Engine_manager::getModule()->events();
		else { // wykonaj eventy dla pozostalych okien
			switch (Engine_manager::getState()) {
			case Engine_state::IS_IN_LC:
				level_editor.events_multiwindow();
				break;
			}
		}
	}

	events_indp();
}

void Engine::events_indp()
{
	static const Uint8 * key = SDL_GetKeyboardState(nullptr);

	if (!escape_pressed && !test) 
	{
		if (key[SDL_SCANCODE_ESCAPE])
			escape_pressed = true;
	}

	if (escape_pressed)
	{
		switch (Engine_manager::getState()) {
		case Engine_state::IS_IN_LC:
			Engine_manager::setState(Engine_state::IS_IN_MENU);
			Menu_manager::set_Menu(Menu_ID::LEVEL_MENU);
			level_editor.reset_states();
			break;
		case Engine_state::IS_IN_ANIMATION_MANAGEMENT:
			Engine_manager::setState(Engine_state::IS_IN_MENU);
			//currentModule = &menu;
			Menu_manager::set_Menu(Menu_ID::ANIMATION_MENU);
			break;
		case Engine_state::IS_IN_MENU:
			switch (Menu_manager::getState()) {
			case Menu_ID::START:
				Engine_manager::Quit();
				break;
			case Menu_ID::ANIMATION_MENU: case Menu_ID::LEVEL_MENU:
				Menu_manager::set_Menu(Menu_ID::START);
				break;
			}
			break;
		}

		escape_pressed = false;
	}

	if (key[SDL_SCANCODE_ESCAPE]) {
		test = true;
		escape_pressed = false;
	}
	else if (!key[SDL_SCANCODE_ESCAPE])
		test = false;

	Engine_manager::getModule()->events_indp();
}

void Engine::events_dpnd()
{
	Engine_manager::getModule()->events();
}

void Engine::render()
{
	if (Engine_manager::get_updateState() != Engine_updateState::RENDER_PREPARING) 
	{
		Renderer::clear();

		Engine_manager::getModule()->render();

		while (!Event_handler::empty()) {
			Event_handler::process();
		}

		Renderer::update();
	}
}
