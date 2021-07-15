#include "Button_input.h"

Button_input::Button_input(SDL_Rect pos, const std::string & teture_path, const char * desctiption, Func onclick, const char * comm) :
	Button{ pos, teture_path }, check_input{ onclick }
{
	window.reset(new Window{ desctiption, 300, 70, SDL_WINDOW_HIDDEN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS });
	input.reset(new InputArea{ window->getRenderer(), { 5, 5, 290, 25 }, 7, 10, "data/fonts/standard_font.ttf", 15, { 255, 0, 0, 255 } });
	komunikat.reset(new Text{ 68, 33, "data/fonts/standard_font.ttf", comm, 25,{ 255, 0, 0, 255 } });

	input->setCurrent(true);
}

Button_input::Button_input(const std::string & teture_path, const char * desctiption, Func onclick, const char * comm) :
	Button{ teture_path }, check_input{ onclick }
{
	window.reset(new Window{ desctiption, 300, 70, SDL_WINDOW_HIDDEN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS });
	input.reset(new InputArea{ window->getRenderer(), { 5, 5, 290, 25 }, 7, 10, "data/fonts/standard_font.ttf", 15, { 255, 0, 0, 255 } });
	komunikat.reset(new Text{ 68, 33, "data/fonts/standard_font.ttf", comm, 25,{ 255, 0, 0, 255 } });

	input->setCurrent(true);
}

void Button_input::events()
{
	Button::events();

	if (window->is_shown())
		input->events();

	if (Keyboard::is_pressedOnce(Key::ENTER)) {
		if (!input->is_empty()) {
			if ((*check_input)(input->getStr())) {
				input->reset();
				window->hide();
				active = false;
			}
			else
			{
				timer.setStart();
				text_active = true;
			}
		}
	}
	else if (Keyboard::is_pressedOnce(Key::ESCAPE)) {
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

		if (text_active && !timer.passed())
			komunikat->render(window->getRenderer());
		else
			text_active = false;

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
