#pragma once
#include "Enemy.h"
#include <vector>
#include "Map_module.h"

class Enemies_placer : public Map_module
{
	friend class Map;
public:
	Enemies_placer(std::vector<Enemy_ptr> & Enemies) : 
		enemies{ Enemies }
	{}

	void objects_events();
	void objects_events_indp();

	void placing_object_events(int map_x, int map_y, int render_x, int render_y) override;
	virtual void single_objectSelecting_events() override {}
	virtual void deleting_objects_events() override {}
private:
	Enemy * current_block;

	bool active_rendering{ true };

	std::vector<Enemy_ptr> & enemies;
};