#pragma once

struct Block_data {
	int map_x, map_y;
};

class Block_OBJ
{
public:
	Block_OBJ() {}

	void render();

	~Block_OBJ() {}
};