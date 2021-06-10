#pragma once
#include <SDL_rect.h>
#include <string>
#include "Text.h"
#include <memory>
#include "Mouse.h"

class CoordinateBar_mouse
{
public:
	// pos - pozycja coordinate_bar
	// rt - adres wzgl�dem kt�rej pozycji aktualizowa� dane
	// ru - dane kt�re wzgl�dem rt b�d� aktualizowane
	//Coordinates_bar(const SDL_Rect & pos, const SDL_Rect * rt, const SDL_Rect * ru);
	CoordinateBar_mouse(const SDL_Rect & pos);

	void events();
	void render();

	int getX() const { return Mouse::getX(); }
	int getY() const { return Mouse::getY(); }

	void set(const SDL_Rect * rt, const SDL_Rect * ru);

	~CoordinateBar_mouse() {}
private:

	void update_text();
private:
	// wzgl�dem kt�rego obszaru aktualizowa� dane
	const SDL_Rect * cord;
	const SDL_Rect * cord2;

	// pozycja wzgl�dem okna
	SDL_Rect position;

	// kordynaty, kt�re b�d� przekonwertowane na string
	int x, y;

	// Tekst wy�wietlany
	std::string render_text;

	//std::unique_ptr<Text> coord_x, coord_y;
	std::unique_ptr<Text> text_to_render;
};