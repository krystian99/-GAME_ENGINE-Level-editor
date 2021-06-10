#pragma once
#include <SDL_rect.h>

class Block // klasa bazowa dla wszystkich bloków - udostêpnia podstawowy interfejs. W razie dodatkowego interfejsu klasy pochodnej, bêdzie mo¿na u¿yæ operatora dynamic_cast<T*>(&t)
{
public:
	virtual void events();
	virtual void render() = 0;

	void set_renderPOS(int x, int y, int w, int h);
	void set_mapPOS(int x, int y, int w, int h);

	void update_renderPOS(int x, int y);
	void update_mapPOS(int x, int y);

	SDL_Rect get_mapPOS() const { return mapPOS; } // zwracanie malych struktur jest wydajniejsze przez wartosc niz przez referencje
	SDL_Rect get_renderPOS() const { return mapPOS; }

	// czy klikniêto jakiœ przycisk na tym obiekcie? -> M1 - klikniêto raz
	bool is_middleM1_pressed() const { return middleM_pressed; }
	bool is_rightM1_pressed() const { return rightM_pressed; }
	bool is_leftM1_pressed() const { return leftM_pressed; }

	virtual ~Block() {}
private:
	void mouse_handler();
	void updateEvent();
private:
	SDL_Rect renderPOS, mapPOS;

	bool middleM_pressed{ false }, rightM_pressed{ false }, leftM_pressed{ false };
};