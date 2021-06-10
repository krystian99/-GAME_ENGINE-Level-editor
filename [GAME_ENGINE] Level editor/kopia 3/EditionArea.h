#pragma once
#include <list>
#include <vector>
#include <fstream>
#include <SDL_events.h>
#include <string>
#include <iterator>

class EditionArea // odpowiada za generowanie w�a�ciwego kodu �r�d�owego, za umieszczanie obiekt�w na okre�lonych pozycjach
{
public:
	EditionArea();

	void generateCode();

	void switch_files(std::string level_name);

	void mouse_handler(SDL_Event * ev);

	~EditionArea();
private:
	void checkEnemies();
	void checkPlayer();

	void generatePlayer();
	void generateEnemies();
private:
	std::ifstream wczytaj; // wczytuje poprzednio za�adowany level

	std::ofstream zapisz; // zapisuje level do kodu �r�d�owego

	struct Object {
		std::string generateTEXT;
		int x, y;
	};
	std::list<Object> enemies;

	Object player_spawn;

	std::list<Object> blocks;
};

