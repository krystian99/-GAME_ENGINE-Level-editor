#pragma once
#include "InputArea.h"
#include <SDL_render.h>
#include "Button.h"
#include <string>
#include <memory>
#include "Window.h"
#include "InputArea.h"
#include "Text.h"
#include "Timer.h"

class Button_input : public Button // po klikniêciu na przycisk ³adowane jest nowe okno i umieszczane na œrodku ekranu. Beda umieszczone tam opcje wyboru: anulowania wyboru i akceptacji
{
	using Func = bool(*)(std::string str);
public:
	Button_input(SDL_Rect pos, const std::string & teture_path, const char * desctiption, Func onclick, const char * comm = "d ");
	Button_input(const std::string & teture_path, const char * desctiption, Func onclick, const char * comm = " d");

	void events();
	void render();
private:
	void on_mouseL1hit() override;
private:
	std::unique_ptr<Text> komunikat;

	Timer timer{ 2000 };
	bool text_active{ false };

	SDL_Rect button_accept, button_cancel;

	Func check_input{ nullptr };

	SDL_Color color_out;

	std::unique_ptr<Window> window;

	bool active{ false };

	bool window_created{ false };

	std::unique_ptr<InputArea> input;

	Texture accept, cancel;
};