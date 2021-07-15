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
	// zdarzenia zale¿ne od myszki oraz klawiatury
	while (SDL_PollEvent(&event_handler)) {

		Keyboard::events(&event_handler);
		Mouse::update(&event_handler);

		if (event_handler.type == SDL_WINDOWEVENT && event_handler.window.windowID == Renderer::get_mainWindow_ID()) {
			switch (event_handler.window.event) {
			case SDL_WINDOWEVENT_CLOSE:
				Engine_manager::Quit();
				break;
			}
		}

		if (event_handler.window.windowID == Renderer::get_mainWindow_ID()) {
			events_dpnd();

			if (Keyboard::is_pressedOnce(Key::ESCAPE) || Keyboard::is_pressedOnce({ Key::LCNTRL, Key::RSHIFT, Key::D })) {
				switch (Engine_manager::getState()) {
				case Engine_state::IS_IN_LC:
					Engine_manager::setState(Engine_state::IS_IN_MENU);
					Menu_manager::set_Menu(Menu_ID::LEVEL_MENU);
					level_editor.reset_states();
					break;
				case Engine_state::IS_IN_ANIMATION_MANAGEMENT:
					Engine_manager::setState(Engine_state::IS_IN_MENU);
					Menu_manager::set_Menu(Menu_ID::ANIMATION_MENU);
					break;
				case Engine_state::IS_IN_MENU:
					switch (Menu_manager::getState()) {
					case Menu_ID::START:
						Engine_manager::Quit();
						break;
					case Menu_ID::LEVEL_MENU:
						Menu_manager::set_Menu(Menu_ID::START);
						break;
					case Menu_ID::ANIMATION_MENU:
						Menu_manager::set_Menu(Menu_ID::START);
						break;
					}
					break;
				}
			}
		}

		// wykonaj eventy dla pozostalych okien
		else {
			switch (Engine_manager::getState()) {
			case Engine_state::IS_IN_LC:
				level_editor.events_multiwindow();
				break;
			}
		}
	}
	// zdarzenia niezale¿ne od myszki i klawiatury
	events_indp();
}

void Engine::events_indp()
{
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

		while (!Event_handler::empty())
			Event_handler::process();

		Renderer::update();
	}
}
