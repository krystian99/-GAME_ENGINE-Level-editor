#include "Enemies_placer.h"
#include "Enemies_placer.h"
#include "Map_manager.h"
#include "Enemy_Types.h"
#include "Map_manager.h"

void Enemies_placer::events()
{

}

void Enemies_placer::render()
{
	Map_manager::render_tempOBJ(edit_area.left(), edit_area.up());
}

/*void Enemies_placer::objects_events()
{
	for (auto & enemy : enemies)
		enemy->events();
}

void Enemies_placer::objects_events_indp()
{

}*/

void Enemies_placer::placing_object_events(int map_x, int map_y, int render_x, int render_y)
{
	using namespace Enemy_Types;

	auto & flip = Map_manager::get_OBJ_orient();

	switch (Map_manager::get_EnemyID())
	{
	case Enemy_ID::TEST:
		enemies.push_back(Enemy_ptr{ new Enemy_Test{ map_x, map_y, flip } });
		break;
	case Enemy_ID::TEST2:
		enemies.push_back(Enemy_ptr{ new Enemy_Test2{ map_x, map_y, flip } });
		break;
	case Enemy_ID::TEST3:
		enemies.push_back(Enemy_ptr{ new Enemy_Test3{ map_x, map_y, flip } });
		break;
	case Enemy_ID::TEST4:
		enemies.push_back(Enemy_ptr{ new Enemy_Test4{ map_x, map_y, flip } });
		break;
	}
	enemies.back()->set_renderPOS(render_x, render_y, Map_manager::get_tempRenderW(), Map_manager::get_tempRenderH());
}