#include "MapOBJ.h"
#include "Map_manager.h"

double MapOBJ::SIZE_MULTIPLIER{ 1.0 };

MapOBJ::MapOBJ(const Rect & render_position, const Rect & map_position) : Object{ render_position }
{
	mapPOS = map_position;
}

MapOBJ::MapOBJ(SDL_Rect map_pos, const Size* sz) : object_size{ sz }
{
	mapPOS = map_pos;
}

MapOBJ::MapOBJ(const int& x, const int& y, const Size* sz) : object_size{ sz }
{
	set_mapPOS(x, y);
}

void MapOBJ::events()
{
	reset_states();

	Object::events();
}

void MapOBJ::render()
{

}

void MapOBJ::set_mapPOS(int x, int y)
{
	mapPOS.set_position(x, y);
}

void MapOBJ::set_mapPOS(int x, int y, int w, int h)
{
	mapPOS.set_position(x, y, w, h);
}

void MapOBJ::set_mapX(int x)
{
	mapPOS.setX(x);
}

void MapOBJ::set_mapY(int y)
{
	mapPOS.setY(y);
}

void MapOBJ::set_selectState(bool st)
{
	selected = st;
}

void MapOBJ::switch_selected_state()
{
	selected = !selected;
}

void MapOBJ::update_Size()
{
	mapPOS.setW(std::round(object_size->mapW * SIZE_MULTIPLIER));
	mapPOS.setH(std::round(object_size->mapH * SIZE_MULTIPLIER));
	setW(std::round(object_size->renderW * SIZE_MULTIPLIER));
	setH(std::round(object_size->renderH * SIZE_MULTIPLIER));
}

void MapOBJ::update_mapPOS(int x, int y)
{
	mapPOS.update_position(x, y);
}


void MapOBJ::set_mapW(int w)
{
	mapPOS.setW(w);
}

void MapOBJ::set_mapH(int h)
{
	mapPOS.setH(h);
}

bool MapOBJ::set_size_multiplier(double size)
{
	if (size == 0)
		return false;
	SIZE_MULTIPLIER = size;
	return true;
}

void MapOBJ::update_multiplierUP()
{
	SIZE_MULTIPLIER += MULTIPLIER_ADD;
	Map_manager::Update_OBJ_sizes();
	Map_manager::set_Update_state(Map_Update_state::UPDATED_OBJECTS_SIZE);
	//return true;
}

void MapOBJ::update_multiplierDOWN()
{
	if (SIZE_MULTIPLIER - MULTIPLIER_ADD > 0.0) {
		SIZE_MULTIPLIER -= MULTIPLIER_ADD;
		Map_manager::Update_OBJ_sizes();
		Map_manager::set_Update_state(Map_Update_state::UPDATED_OBJECTS_SIZE);
	}
}

void MapOBJ::reset_multiplier()
{
	SIZE_MULTIPLIER = 1.0;
}

void MapOBJ::reset_states()
{
	clicked = false;
}

void MapOBJ::on_mouseL1hit()
{
	clicked = true;
}
