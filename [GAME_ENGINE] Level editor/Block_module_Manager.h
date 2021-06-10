#pragma once
#include "Block_types.h"

class Block_module_Manager
{
public:

	static Block_types getType() { return type; }

private:
	static Block_types type;
};