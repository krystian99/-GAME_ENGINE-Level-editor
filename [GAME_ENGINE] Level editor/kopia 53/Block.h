#pragma once
#include <SDL_rect.h>
#include "Object.h"
#include "Texture.h"

class Block : public Object // klasa bazowa dla wszystkich blok�w - udost�pnia podstawowy interfejs. W razie dodatkowego interfejsu klasy pochodnej, b�dzie mo�na u�y� operatora dynamic_cast<T*>(&t)
{
public:
	virtual void events();
	virtual void render();

	void set_mapPOS(int x, int y, int w, int h);
	void update_mapPOS(int x, int y);
	SDL_Rect get_mapPOS() const { return mapPOS; } // zwracanie malych struktur jest wydajniejsze przez wartosc niz przez referencje

	const Texture & get_TX() const { return texture; }

	bool is_connected() const { return connected; } // czy istnieje jaka� relacja z innym blokiem?

	void connect_with(Block * block);

	virtual ~Block() {}
private:
	bool connected{ false };

	Block * connectedBlock; // blok po��czony z tym blokiem

	Texture texture;

	SDL_Rect mapPOS;
};