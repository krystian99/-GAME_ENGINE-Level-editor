#pragma once
#include <SDL_render.h>
#include <string>
#include "ScrollBar.h"


class ScroolBar_mapModules // osobna przestrzen dla danych i zdarze� tego konkretnego ScrollBar'a. To samo trzeba zrobi� z reszt�.
{
public:
	ScroolBar_mapModules(SDL_Rect position);

	void render();
	void events();
private:
	ScrollBar map_modules;
};