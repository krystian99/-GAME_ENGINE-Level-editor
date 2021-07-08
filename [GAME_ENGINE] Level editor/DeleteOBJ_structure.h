#pragma once
#include "Module_base.h"
#include <vector>
#include "Enemy.h"

class DeleteOBJ_structure : public Module_base
{
	using Enemies = std::vector<Enemy_ptr>;
public:
	DeleteOBJ_structure(Enemies& en) : 
		enemies{ en }
	{}

	void events();
	void events_indp() {}

	void render() {}
private:
	Enemies& enemies;
};
