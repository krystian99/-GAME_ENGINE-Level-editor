#pragma once
#include <SDL_events.h>
#include <SDL_render.h>

class Window
{
public:
	Window(const char * title, int w, int h, Uint32 window_flags);

	void handleEvent(SDL_Event & e);
	void focus();

	void clearRenderer();
	void updateRenderer();

	//void render();

	void set_DrawColor(SDL_Color Color);
	void hide();
	void show();

	SDL_Renderer * getRenderer() const { return renderer; }

	int getWidth() const { return Width; }
	int getHeight() const { return Height; }

	bool has_MouseFocus() const { return MouseFocus; }
	bool has_KeyboardFocus() const { return KeyboardFocus; }
	bool is_minimized() const { return Minimized; }
	bool is_shown() const { return Shown; }

	~Window();
private:
	SDL_Window * window;
	SDL_Renderer* renderer;
	int window_ID;

	int Width;
	int Height;

	SDL_Color render_color;

	bool MouseFocus;
	bool KeyboardFocus;
	bool FullScreen;
	bool Minimized;
	bool Shown;
};