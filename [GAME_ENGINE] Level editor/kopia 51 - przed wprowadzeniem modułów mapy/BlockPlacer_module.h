#pragma once
#include "Block.h"
#include <vector>

class BlockPlacer_module
	// klasa ta bêdzie czêœci¹ klasy Map. Zosta³a specjalnie oddzielona, bo bêdzie zawiera³a mnóstwo metod. Gdyby nie zosta³a utworzona
	// kod klasy Map by³by niesamowice trudny w rozszerzeniu. Tak¿e spróbujê zrobiæ wszystko, by interfejs by³ prosty i zarazem, by
	// móg³ komunikowaæ siê z g³ówn¹ klas¹ opercujc¹(tutaj Map).
{
public:
	BlockPlacer_module(std::vector<Block*> & Blocks) : 
		blocks{ Blocks }
	{}

	void events();
	void events_indp();

	void render();

	void set_viewActive(bool b) { active_rendering = true; } // ustal, czy obiekty maj¹ byæ widoczne -> raczej ta funkcja zostanie przerzucona do BlockPlacer_manager

	void set_currentOBJ(Block *& block); // ustalane na podstawie klikniêcia na obiekt -> musi byæ w oddzielnym interfejsie, bo 
										// obiekty mog¹ byæ po³¹czone i przenoszenie jednego obiektu, mo¿e przesuwaæ po³¹czon¹ ca³oœæ

	void moving_events(); // przenoszenie obiektów
	void placing_events(); // stawianie obiektów
private: 
	// funkcje

private:
	Block * current_block;

	bool active_rendering{ true };

	std::vector<Block*> & blocks;
};