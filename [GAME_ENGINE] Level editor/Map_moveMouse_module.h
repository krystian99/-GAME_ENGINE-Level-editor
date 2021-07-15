#pragma once
#include <vector>
#include "Enemy.h"
#include "Texture.h"
#include "Module_base.h"

class Map_moveMouse_module : public Module_base, public Object
{
	using Enemies = std::vector<Enemy_ptr>;
public:
	Map_moveMouse_module(Enemies& en, Rect& mapbg_rect, Rect& edit_a, const Texture& mapBG_TX) :
		enemies{ en }, mapBG_area{ mapbg_rect }, edit_area{ edit_a }, mapBG{ mapBG_TX }
	{}

	void events();
private:
	void on_mouseL_press() override;
private:
	const Texture& mapBG;

	Rect& mapBG_area, & edit_area;

	Enemies& enemies;
};
