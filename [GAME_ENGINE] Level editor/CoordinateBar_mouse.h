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
	// rt - adres wzglêdem której pozycji aktualizowaæ dane
	// ru - dane które wzglêdem rt bêd¹ aktualizowane
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
	// wzglêdem którego obszaru aktualizowaæ dane
	const SDL_Rect * cord;
	const SDL_Rect * cord2;

	// pozycja wzglêdem okna
	SDL_Rect position;

	// kordynaty, które bêd¹ przekonwertowane na string
	int x, y;

	// Tekst wyœwietlany
	std::string render_text;

	//std::unique_ptr<Text> coord_x, coord_y;
	std::unique_ptr<Text> text_to_render;
};