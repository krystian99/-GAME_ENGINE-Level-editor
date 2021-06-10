#pragma once
#include "Block.h"
#include <vector>
#include "Map_module.h"

class BlockPlacer_module : public Map_module
	// klasa ta bêdzie czêœci¹ klasy Map. Zosta³a specjalnie oddzielona, bo bêdzie zawiera³a mnóstwo metod. Gdyby nie zosta³a utworzona
	// kod klasy Map by³by niesamowice trudny w rozszerzeniu. Tak¿e spróbujê zrobiæ wszystko, by interfejs by³ prosty i zarazem, by
	// móg³ komunikowaæ siê z g³ówn¹ klas¹ opercujc¹(tutaj Map).
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