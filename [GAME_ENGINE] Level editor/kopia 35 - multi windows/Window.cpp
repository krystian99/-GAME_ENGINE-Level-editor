#include "Window.h"
#include "Video_Info.h"
#include <algorithm>
#include "Error.h"

Window::Window(const char * title, int w, int h, Uint32 window_flags)
{
	w = std::round(Video_Info::get_scaleW() * w);
	h = std::round(Video_Info::get_scaleH() * h);

	if (!(window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, window_flags)))
		throw Error::throw_Message("Error: Cannot create window!");

	if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		throw Error::throw_Message("Eror: Cannot create renderer!");
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	window_ID = SDL_GetWindowID(window);
	Shown = true;
}

void Window::handleEvent(SDL_Event & e)
{
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == window_ID)
	{
		switch (e.window.event)
		{
			//Window appeared
		case SDL_WINDOWEVENT_SHOWN:
			Shown = true;
			break;

			//Window disappeared
		case SDL_WINDOWEVENT_HIDDEN:
			Shown = false;
			break;

			//Get new dimensions and repaint
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			Width = e.window.data1;
			Height = e.window.data2;
			SDL_RenderPresent(renderer);
			break;

			//Repaint on expose
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(renderer);
			break;

			//Mouse enter
		case SDL_WINDOWEVENT_ENTER:
			MouseFocus = true;
			break;

			//Mouse exit
		case SDL_WINDOWEVENT_LEAVE:
			MouseFocus = false;
			break;

			//Keyboard focus gained
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			KeyboardFocus = true;
			break;

			//Keyboard focus lost
		case SDL_WINDOWEVENT_FOCUS_LOST:
			KeyboardFocus = false;
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			Minimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			Minimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			Minimized = false;
			break;

			//Hide on close
		case SDL_WINDOWEVENT_CLOSE:
			SDL_HideWindow(window);
			break;
		}
	}
}

void Window::focus()
{
	//Restore window if needed
	if (!Shown)
		SDL_ShowWindow(window);

	//Move window forward
	SDL_RaiseWindow(window);
}

void Window::clearRenderer()
{
	SDL_RenderClear(renderer);
}

void Window::updateRenderer()
{
	SDL_RenderPresent(renderer);
}

/*void Window::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}*/

void Window::set_DrawColor(SDL_Color Color)
{
	render_color = Color;
}

void Window::hide()
{
	SDL_HideWindow(window);
}

void Window::show()
{
	SDL_ShowWindow(window);
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}