#include "BlockPlacer_module.h"

void BlockPlacer_module::events()
{

}

void BlockPlacer_module::events_indp()
{

}

void BlockPlacer_module::render()
{

}

void BlockPlacer_module::set_currentOBJ(Block *& block)
{
	current_block = block;
}

void BlockPlacer_module::moving_events()
{
	if (current_block->is_connected()) // przesu� o t� sam� odleg�o�� bloki po��czone z tym konkretnym blokiem
	{

	}
}

void BlockPlacer_module::placing_events()
{

}