#pragma once
#include <SDL_render.h>
#include "ScrollBar.h"
#include <string>

// v1 - dodano klas�

class LevelCreator // odpowiada za generowanie w�a�ciwego kodu �r�d�owego, za umieszczanie obiekt�w na okre�lonych pozycjach
{
public:
	LevelCreator(const SDL_DisplayMode * dm);

	void setPosition(const SDL_DisplayMode * dm); // ustala pozycje wszystkich przycisk�w, scrollbari itp.

	void render(SDL_Renderer * rn);

	void load_level(std::string str);
	void save_level(std::string str);

	void mouse_handler(); // zdarzenia myszy
private:
	ScrollBar sbDynamic, sbKey, sbStatic;
	// vector<Enemies*> enemies;
	// Player pl;
	// vector<KeyObject*> keyobjects;
};

