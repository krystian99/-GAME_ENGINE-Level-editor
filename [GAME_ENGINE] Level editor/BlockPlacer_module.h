#pragma once
#include "Block.h"
#include <vector>
#include "Map_module.h"

class BlockPlacer_module : public Map_module
	// klasa ta b�dzie cz�ci� klasy Map. Zosta�a specjalnie oddzielona, bo b�dzie zawiera�a mn�stwo metod. Gdyby nie zosta�a utworzona
	// kod klasy Map by�by niesamowice trudny w rozszerzeniu. Tak�e spr�buj� zrobi� wszystko, by interfejs by� prosty i zarazem, by
	// m�g� komunikowa� si� z g��wn� klas� opercujc�(tutaj Map).
{
public:
	BlockPlacer_module(std::vector<Block*> & Blocks) : 
		blocks{ Blocks }
	{}

	void objects_events();
	void objects_events_indp();

	void placing_object_events(int map_x, int map_y, int render_x, int render_y) override;
private:
	Block * current_block;

	bool active_rendering{ true };

	std::vector<Block*> & blocks;
};