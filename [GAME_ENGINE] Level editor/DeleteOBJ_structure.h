#pragma once
#include "Module_base.h"
#include <vector>
#include "Enemy.h"
#include "Object.h"

class DeleteOBJ_structure : public Module_base, public Object
{
	using Enemies = std::vector<Enemy_ptr>;
public:
	DeleteOBJ_structure(Enemies& en) : 
		enemies{ en }
	{}

	void events();
private:
	void on_mouseL1hit() override;
private:
	Enemies& enemies;
};
