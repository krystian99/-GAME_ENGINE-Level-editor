#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

namespace Dynamic {
	string addEnemy(int x, int y);
	string setSpawnPlayer(int x, int y);
	// ...
}

namespace Static {
	string addBlock(int x, int y);
}

namespace Key {
	string addSomething(int x, int y); // TEST
}