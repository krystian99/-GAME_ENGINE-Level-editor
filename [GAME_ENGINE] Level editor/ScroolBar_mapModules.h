#pragma once
#include <SDL_render.h>
#include <string>
#include "ScrollBar.h"


class ScroolBar_mapModules // osobna przestrzen dla danych i zdarzeñ tego konkretnego ScrollBar'a. To samo trzeba zrobiæ z reszt¹.
{
public:
	ScroolBar_mapModules(SDL_Rect position);

	void render();
	void events();
private:
	ScrollBar<ScrollBar_orient::VERTICAL, Render_state::TEXTURE> map_modules;
};