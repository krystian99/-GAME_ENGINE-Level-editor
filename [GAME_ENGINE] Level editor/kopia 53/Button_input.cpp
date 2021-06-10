#include "Button_input.h"
#include "Video_Info.h"
#include <SDL_keyboard.h>
#include "LevelEditor_manager.h"

Button_input::Button_input(SDL_Rect pos, const std::string & teture_path, const char * desctiption, Func onclick) :
	Button{ pos, teture_path }, check_input{ onclick }
{
	window.reset(new Window{ desctiption, 300, 70, SDL_WINDOW_HIDDEN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS });
	input.reset(new InputArea{ window->getRenderer(), { 5, 5, 290, 25 }, 7, 10, "data/fonts/standard_font.ttf", 15, { 255, 0, 0, 255 } });

	input->setCurrent(true);
	button_accept = { 5, 35, 40, 30 };
	button_cancel = { 255, 35, 40, 30 };

	accept.loadFromFile(window->getRenderer(), "data/button_input/accept.png");
	cancel.loadFromFile(window->getRenderer(), "data/button_input/cancel.png");
}

Button_input::Button_input(const std::string & teture_path, const char * desctiption, Func onclick) :
	Button{ teture_path }, check_input{ onclick }
{
	window.reset(new Window{ desctiption, 300, 70, SDL_WINDOW_HIDDEN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS });
	input.reset(new InputArea{ window->getRenderer(), { 5, 5, 290, 25 }, 7, 10, "data/fonts/standard_font.ttf", 15, { 255, 0, 0, 255 } });

	input->setCurrent(true);
	button_accept = { 5, 35, 40, 30 };
	button_cancel = { 255, 35, 40, 30 };

	accept.loadFromFile(window->getRenderer(), "data/button_input/accept.png");
	cancel.loadFromFile(window->getRenderer(), "data/button_input/cancel.png");
}

void Button_input::events()
{
	static const Uint8 * key = SDL_GetKeyboardState(nullptr);

	Button::events();
	if (window->is_shown())
		input->events();

	if (key[SDL_SCANCODE_RETURN]) {
		if (!input->is_empty()) {
			if ((*check_input)(input->getStr())) {
				input->reset();
				window->hide();
				active = false;
			}
		}
	}
	else if (key[SDL_SCANCODE_ESCAPE]) {
		input->reset();
		window->hide();
		active = false;
	}
}

void Button_input::render()
{
	Button::render();

	if (active) {
		window->clearRenderer();

		input->render(window->getRenderer());
		accept.render(window->getRenderer(), nullptr, &button_accept);
		cancel.render(window->getRenderer(), nullptr, &button_cancel);

		window->updateRenderer();
	}
}

void Button_input::on_mouseL1hit()
{
	if (!active) {
		window->show();
		active = true;
	}
	else {
		active = !active;
		window->hide();
	}
}