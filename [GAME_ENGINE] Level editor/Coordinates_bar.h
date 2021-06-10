#pragma once
#include <SDL_rect.h>
#include <string>
#include "Text.h"
#include <memory>

enum class CoordinateBar_state{ OTHER, STANDARD };

class Coordinates_bar
{
public:
	// pos - pozycja coordinate_bar
	// rt - adres wzgl�dem kt�rej pozycji aktualizowa� dane
	// ru - dane kt�re wzgl�dem rt b�d� aktualizowane
	//Coordinates_bar(const SDL_Rect & pos, const SDL_Rect * rt, const SDL_Rect * ru);
	Coordinates_bar(const SDL_Rect & pos);
	void events();
	void render();

	int getX() const { return x; }
	int getY() const { return y; }

	void set(const SDL_Rect * rt, const SDL_Rect * ru);
	void set(double scaleX, double scaleY);

	~Coordinates_bar() {}
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

	CoordinateBar_state state;

	//std::unique_ptr<Text> coord_x, coord_y;
	std::unique_ptr<Text> text_to_render;
};