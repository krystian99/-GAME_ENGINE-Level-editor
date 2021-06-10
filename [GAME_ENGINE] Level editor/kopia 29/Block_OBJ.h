#pragma once
#include "Map_OBJ.h"

enum class Block_ID { TEST }; // TEST - testowy obiekt

struct Block_data : public MapOBJ_data
{
	Block_ID id;
};

class Block_OBJ : public Map_OBJ
{
public:
	Block_OBJ(const int & x, const int & y, Block_ID ID);

	void render();

	~Block_OBJ() {}
private:
	Block_ID id;
};