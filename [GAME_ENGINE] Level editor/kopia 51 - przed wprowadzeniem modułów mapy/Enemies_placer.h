#pragma once
#include "Enemy.h"
#include <vector>

class Enemies_placer
{
public:
	Enemies_placer(std::vector<Enemy*> & Enemies) : 
		enemies{ Enemies }
	{}

	void events();
	void events_indp();

	void render();

	void set_currentOBJ(Enemy *& enemy);

	void set_viewActive(bool b) { active_rendering = true; }

	void moving_events(); // przenoszenie obiektów
	void placing_events(); // stawianie obiektów
private:
	// funkcje

private:
	Enemy * current_block;

	bool active_rendering{ true };

	std::vector<Enemy*> & enemies;
};

