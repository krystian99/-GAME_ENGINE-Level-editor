#include "Button_Functions.h"

string Dynamic::addEnemy(int x, int y)
{
	return "AddEnemy(" + std::to_string(x) + ", " + std::to_string(y) + ");";
}

string Dynamic::setSpawnPlayer(int x, int y)
{
	return string();
}

string Static::addBlock(int x, int y)
{
	return string();
}

string Key::addSomething(int x, int y)
{
	return string();
}
