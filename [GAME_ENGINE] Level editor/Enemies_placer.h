#pragma once
#include "Enemy.h"
#include <vector>
#include "Module_base.h"
#include "Rect.h"

class Enemies_placer : Module_base
{
	using Enemies = std::vector<Enemy_ptr>;
public:
	Enemies_placer(Enemies& Enemies, const Rect& edit_a) :
		enemies{ Enemies }, edit_area{ edit_a }
	{}

	void events() override;

	void render() override;

	//void objects_events();
	//void objects_events_indp();

	void placing_object_events(int map_x, int map_y, int render_x, int render_y);
private:
	Enemy * current_block;

	const Rect& edit_area;

	bool active_rendering{ true };

	std::vector<Enemy_ptr> & enemies;
};
