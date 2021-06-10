#pragma once
#include <SDL_render.h>
#include "ScrollBar.h"
#include <string>

// v1 - dodano klasê

class LevelCreator // odpowiada za generowanie w³aœciwego kodu Ÿród³owego, za umieszczanie obiektów na okreœlonych pozycjach
{
public:
	LevelCreator(const SDL_DisplayMode * dm);

	void setPosition(const SDL_DisplayMode * dm); // ustala pozycje wszystkich przycisków, scrollbari itp.

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

