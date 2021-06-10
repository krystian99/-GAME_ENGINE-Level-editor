#pragma once
#include <vector>
#include <string>
#include "Button_Functions.h"
#include "Buttons_textures.h"

namespace Button_resources {
	using std::string;
	using std::vector;
	const vector<string(*)(int, int)> dynamic_functions
	{
		Dynamic::setSpawnPlayer,
		Dynamic::addEnemy
	};

	const vector<string(*)(int, int)> static_functions{ // itd.
		Static::addBlock
	};

	const vector<string(*)(int, int)> key_functions{ // itd.
		Key::addSomething
	};
}