#pragma once
#include <SDL_rect.h>
#include <string>
#include "Text.h"
#include <memory>

class CoordinateBar_map
{
public:
	// pos - pozycja coordinate_bar
	// rt - adres wzgl�dem kt�rej pozycji aktualizowa� dane
	// ru - dane kt�re wzgl�dem rt b�d� aktualizowane
	//Coordinates_bar(const SDL_Rect & pos, const SDL_Rect * rt, const SDL_Rect * ru);
	//CoordinateBar_map(const SDL_Rect& pos);
	static void events(bool mouse_over);
	static void render(bool mouse_over);

	static void Init(const SDL_Rect& pos, const SDL_Rect* edit_a, const SDL_Rect* map_a);

	static int getX() { return x; }
	static int getY() { return y; }

	static void set(double scaleX, double scaleY);

private:
	static void update_text();
private:
	// wzgl�dem kt�rego obszaru aktualizowa� dane
	static const SDL_Rect* edit_area;
	static const SDL_Rect* map_area;

	// pozycja wzgl�dem okna
	static SDL_Rect position;

	// kordynaty, kt�re b�d� przekonwertowane na string
	static int x, y;

	// Tekst wy�wietlany
	static std::string render_text;

	//std::unique_ptr<Text> coord_x, coord_y;
	static std::unique_ptr<Text> text_to_render;
};

