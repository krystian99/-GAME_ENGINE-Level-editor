#include "Environment.h"
#include "Engine_manager.h"
#include "Menu_manager.h"
#include "LevelEditor_manager.h"
#include "Mouse.h"
#include "Renderer.h"
#include "Keyboard.h"

void Environment::run()
{
	while (Engine_manager::is_running()) {
		events();
		render();
	}
}

void Environment::events() 
{
	while (SDL_PollEvent(&event_handler)) // zdarzenia zale¿ne od aktualizacji 
	{
		Keyboard::events(&event_handler);
		Mouse::update(&event_handler);

		/*if (Keyboard::getState() == Key::ESCAPE)
		{
			switch (Engine_manager::getState()) {
			case Engine_state::IS_IN_LC:
				Engine_manager::setState(Engine_state::IS_IN_MENU);
				Menu_manager::set_Menu(Menu_ID::LEVEL_MENU);
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
				case Menu_ID::ANIMATION_MENU: case Menu_ID::LEVEL_MENU:
					Menu_manager::set_Menu(Menu_ID::START);
					break;
				}
				break;
			}
		}*/
		if (event_handler.type == SDL_WINDOWEVENT && event_handler.window.windowID == Renderer::get_mainWindow_ID()) {
			switch (event_handler.window.event) {
			case SDL_WINDOWEVENT_CLOSE:
				Engine_manager::Quit();
				break;
			}
		}

		if (event_handler.window.windowID == Renderer::get_mainWindow_ID())
			events_dpnd();
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

void Environment::events_indp()
{
	static const Uint8 * key = SDL_GetKeyboardState(nullptr);
	if (!escape_pressed && !test) {
		if (key[SDL_SCANCODE_ESCAPE])
			escape_pressed = true;
	}

	if (escape_pressed)
	{

		switch (Engine_manager::getState()) {
		case Engine_state::IS_IN_LC:
			Engine_manager::setState(Engine_state::IS_IN_MENU);
			Menu_manager::set_Menu(Menu_ID::LEVEL_MENU);
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

	switch (Engine_manager::getState())
	{
	case Engine_state::IS_IN_MENU:
		menu.events_indp();
		break;
	case Engine_state::IS_IN_LC:
		level_editor.events_indp();
		break;
	case Engine_state::IS_IN_ANIMATION_MANAGEMENT:
		animation_config_creator.events_indp();
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
	case Engine_state::IS_IN_ANIMATION_MANAGEMENT:
		animation_config_creator.events();
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
	case Engine_state::IS_IN_ANIMATION_MANAGEMENT:
		animation_config_creator.render();
		break;
	}
	Renderer::update();
}