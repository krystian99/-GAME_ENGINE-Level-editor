#include "Block.h"
#include "Mouse.h"

void Block::events()
{
	
}

void Block::set_mapPOS(int x, int y, int w, int h)
{
	mapPOS = { x, y, w, h };
}

void Block::update_mapPOS(int x, int y)
{
	mapPOS.x = x;
	mapPOS.y = y;
}

void Block::connect_with(Block * block)
{
	connectedBlock = block;
}