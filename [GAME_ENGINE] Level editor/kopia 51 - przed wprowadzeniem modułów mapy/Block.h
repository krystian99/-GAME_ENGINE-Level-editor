#pragma once
#include <SDL_rect.h>
#include "Object.h"
#include "Texture.h"

class Block : public Object // klasa bazowa dla wszystkich bloków - udostêpnia podstawowy interfejs. W razie dodatkowego interfejsu klasy pochodnej, bêdzie mo¿na u¿yæ operatora dynamic_cast<T*>(&t)
{
public:
	virtual void events();
	virtual void render();

	void set_mapPOS(int x, int y, int w, int h);
	void update_mapPOS(int x, int y);
	SDL_Rect get_mapPOS() const { return mapPOS; } // zwracanie malych struktur jest wydajniejsze przez wartosc niz przez referencje

	const Texture & get_TX() const { return texture; }

	bool is_connected() const { return connected; } // czy istnieje jakaœ relacja z innym blokiem?

	void connect_with(Block * block);

	virtual ~Block() {}
private:
	bool connected{ false };

	Block * connectedBlock; // blok po³¹czony z tym blokiem

	Texture texture;

	SDL_Rect mapPOS;
};