#pragma once
#include "Block.h"
#include <vector>

class BlockPlacer_module
	// klasa ta b�dzie cz�ci� klasy Map. Zosta�a specjalnie oddzielona, bo b�dzie zawiera�a mn�stwo metod. Gdyby nie zosta�a utworzona
	// kod klasy Map by�by niesamowice trudny w rozszerzeniu. Tak�e spr�buj� zrobi� wszystko, by interfejs by� prosty i zarazem, by
	// m�g� komunikowa� si� z g��wn� klas� opercujc�(tutaj Map).
{
public:
	BlockPlacer_module(std::vector<Block*> & Blocks) : 
		blocks{ Blocks }
	{}

	void events();
	void events_indp();

	void render();

	void set_viewActive(bool b) { active_rendering = true; } // ustal, czy obiekty maj� by� widoczne -> raczej ta funkcja zostanie przerzucona do BlockPlacer_manager

	void set_currentOBJ(Block *& block); // ustalane na podstawie klikni�cia na obiekt -> musi by� w oddzielnym interfejsie, bo 
										// obiekty mog� by� po��czone i przenoszenie jednego obiektu, mo�e przesuwa� po��czon� ca�o��

	void moving_events(); // przenoszenie obiekt�w
	void placing_events(); // stawianie obiekt�w
private: 
	// funkcje

private:
	Block * current_block;

	bool active_rendering{ true };

	std::vector<Block*> & blocks;
};