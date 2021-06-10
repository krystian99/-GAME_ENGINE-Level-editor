#include "EditionArea.h"
#include "Mouse.h"
#include "Exceptions.h"

EditionArea::EditionArea() :
	zapisz { "Generated.txt", std::ios_base::app | std::ios_base::out },
	wczytaj { "Generated.txt", std::ios_base::app | std::ios_base::in }
{
	if (!zapisz.is_open() || !wczytaj.is_open())
		throw Error{ "Cannot load file" };
}

void EditionArea::generateCode()
{
	generateEnemies();
	generatePlayer();
}


void EditionArea::mouse_handler(SDL_Event * ev)
{
	Mouse::update(ev);
	checkEnemies();
	checkPlayer();
}

EditionArea::~EditionArea()
{

}

void EditionArea::checkEnemies()
{

}

void EditionArea::checkPlayer()
{

}

void EditionArea::generatePlayer()
{

}

void EditionArea::generateEnemies()
{
	//std::copy(enemies.begin(), enemies.end(), std::ostream_iterator<std::string>{zapisz, "\n"});
}
