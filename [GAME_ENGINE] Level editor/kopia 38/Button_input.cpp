#include "Button_input.h"
#include "Video_Info.h"
#include <SDL_keyboard.h>
#include "LevelEditor_manager.h"

Button_input::Button_input(SDL_Rect pos, const std::string & teture_path) :
	Button{ pos, teture_path }
{
	window.reset(new Window{ "Input", 300, 70, SDL_WINDOW_HIDDEN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS });
	input.reset(new InputArea{ window->getRenderer(), { 5, 5, 290, 25 }, 7, 10, "data/fonts/standard_font.ttf", 15,{ 255, 0, 0, 255 } });

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
			if (LevelEditor_manager::loadLevel(input->getStr())) {
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
	/*SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);*/

	if (active) {
		window->clearRenderer();

		input->render(window->getRenderer());
		accept.render(window->getRenderer(), nullptr, &button_accept);
		cancel.render(window->getRenderer(), nullptr, &button_cancel);

		window->updateRenderer();
	}
}

void Button_input::onClick()
{
	//Button::onClick();
	if (!active) {
		/*window = SDL_CreateWindow("Input", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, std::round(Video_Info::get_scaleW() * 300), std::round(Video_Info::get_scaleH() * 40), SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		SDL_RaiseWindow(window);*/
		//window.reset(new Window{ "Input", 300, 70, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS /*| SDL_WINDOW_INPUT_GRABBED*/ | SDL_WINDOW_MOUSE_FOCUS });
		
		window->show();
		active = true;
	}
	else {
		active = !active;
		/*SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);*/
		//window.reset();

		window->hide();
	}
}

void Button_input::onMouseOver()
{

}