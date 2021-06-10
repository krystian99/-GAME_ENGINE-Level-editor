#pragma once
#include "InputArea.h"
#include <SDL_render.h>
#include "Button.h"
#include <string>
#include <memory>
#include "Window.h"
#include "InputArea.h"

class Button_input : public Button // po klikniêciu na przycisk ³adowane jest nowe okno i umieszczane na œrodku ekranu. Beda umieszczone tam opcje wyboru: anulowania wyboru i akceptacji
{
	using Func = bool(*)(std::string str);
public:
	Button_input(SDL_Rect pos, const std::string & teture_path, const char * desctiption, Func onclick);
	Button_input(const std::string & teture_path, const char * desctiption, Func onclick);

	void events();
	void render();
private:
	void onClick();
	void onMouseOver();
private:
	/*SDL_Window * window;
	SDL_Renderer * renderer;*/

	SDL_Rect button_accept, button_cancel;

	Func check_input{ nullptr };

	std::unique_ptr<Window> window;

	bool active{ false };

	bool window_created{ false };

	std::unique_ptr<InputArea> input;

	Texture accept, cancel;
};