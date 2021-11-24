#include "MapOBJ.h"
#include "Map_manager.h"

double MapOBJ::SIZE_MULTIPLIER{ 1.0 };

MapOBJ::MapOBJ(const Rect & render_position, const Rect & map_position, Texture* tx) : Object{ render_position }
{
	this->tx = tx;

	mapPOS = map_position;
}

MapOBJ::MapOBJ(SDL_Rect map_pos, const Size* sz, Texture* tx) : object_size{ sz }
{
	this->tx = tx;

	mapPOS = map_pos;
}

MapOBJ::MapOBJ(const int& x, const int& y, const Size* sz, Texture* tx) : object_size{ sz }
{
	this->tx = tx;
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

void MapOBJ::set_mapPOS(Rect&& area)
{
	mapPOS = std::move(area);
}

void MapOBJ::set_mapPOS(int renderX, int renderY, const Rect& edit_area, const Rect& mapBG_area)
{
	double scaleTX_w, scaleTX_h;
	int x, y;

	scaleTX_w = double(renderX - edit_area.left()) / edit_area.getW();
	scaleTX_h = double(renderY - edit_area.up()) / edit_area.getH();

	x = mapBG_area.left() + round(mapBG_area.getW() * scaleTX_w);
	y = mapBG_area.up() + round(mapBG_area.getH() * scaleTX_h);

	set_mapPOS(x, y);
	set_renderPOS(edit_area, mapBG_area);
}

void MapOBJ::set_mapPOS(int renderX, int renderY, int renderW, int renderH, const Rect& edit_area, const Rect& mapBG_area)
{
	double scaleTX_left, scaleTX_up, scaleTX_W, scaleTX_H;
	int x, y, w, h; // dla mapy

	scaleTX_left = double(renderX - edit_area.left()) / edit_area.getW();
	scaleTX_up = double(renderY - edit_area.up()) / edit_area.getH();

	scaleTX_W = double(renderW) / edit_area.getW();
	scaleTX_H = double(renderH) / edit_area.getH();

	x = mapBG_area.left() + round(mapBG_area.getW() * scaleTX_left);
	y = mapBG_area.up() + round(mapBG_area.getH() * scaleTX_up);

	w = round((mapBG_area.right() - mapBG_area.left()) *scaleTX_W);
	h = round((mapBG_area.down() - mapBG_area.up()) * scaleTX_H);

	set_mapPOS(x, y, w, h);

	// dostosuj renderowanie do mapy(mo¿liwe skalowanie)
	set_renderPOS(x, y, w, h, edit_area, mapBG_area);
}

void MapOBJ::set_mapPOS(const Rect& edit_area, const Rect& mapBG_area)
{
	double scaleTX_w, scaleTX_h;
	int x, y;

	scaleTX_w = double(left() - edit_area.left()) / edit_area.getW();
	scaleTX_h = double(up() - edit_area.up()) / edit_area.getH();

	x = mapBG_area.left() + round(mapBG_area.getW() * scaleTX_w);
	y = mapBG_area.up() + round(mapBG_area.getH() * scaleTX_h);

	set_mapPOS(x, y);

	set_renderPOS(edit_area, mapBG_area);
}

void MapOBJ::set_mapX(int x)
{
	mapPOS.setX(x);
}

void MapOBJ::set_mapY(int y)
{
	mapPOS.setY(y);
}

void MapOBJ::set_renderPOS(int mapX, int mapY, int mapW, int mapH, const Rect& edit_area, const Rect& mapBG_area)
{
	int RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H;
	double scaleX, scaleY, scaleW, scaleH;

	scaleX = double(mapX - mapBG_area.left()) / double(mapBG_area.getW());
	scaleY = double(mapY - mapBG_area.up()) / double(mapBG_area.getH());

	scaleW = double(mapW) / double(mapBG_area.right() - mapBG_area.left());
	scaleH = double(mapH) / double(mapBG_area.down() - mapBG_area.up());

	RenderPOS_X = round(scaleX * edit_area.getW()) + edit_area.left();
	RenderPOS_Y = round(scaleY * edit_area.getH()) + edit_area.up();

	RenderPOS_W = round(scaleW * edit_area.getW());
	RenderPOS_H = round(scaleH * edit_area.getH());

	set_position(RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H);
}

void MapOBJ::set_renderPOS(SDL_Rect map, const Rect& edit_area, const Rect& mapBG_area)
{
	int RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H;
	double scaleX, scaleY, scaleW, scaleH;

	scaleX = double(map.x - mapBG_area.left()) / double(mapBG_area.getW());
	scaleY = double(map.y - mapBG_area.up()) / double(mapBG_area.getH());

	scaleW = double(map.w) / double(mapBG_area.right() - mapBG_area.left());
	scaleH = double(map.h) / double(mapBG_area.down() - mapBG_area.up());

	RenderPOS_X = round(scaleX * edit_area.getW()) + edit_area.left();
	RenderPOS_Y = round(scaleY * edit_area.getH()) + edit_area.up();

	RenderPOS_W = round(scaleW * edit_area.getW());
	RenderPOS_H = round(scaleH * edit_area.getH());

	set_position(RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H);
}

void MapOBJ::set_renderPOS(const Rect& edit_area, const Rect& mapBG_area)
{
	int RenderPOS_X, RenderPOS_Y;
	double scaleX, scaleY;

	scaleX = double(get_mapX() - mapBG_area.left()) / double(mapBG_area.getW());
	scaleY = double(get_mapY() - mapBG_area.up()) / double(mapBG_area.getH());

	RenderPOS_X = round(scaleX * edit_area.getW()) + edit_area.left();
	RenderPOS_Y = round(scaleY * edit_area.getH()) + edit_area.up();

	set_position(RenderPOS_X, RenderPOS_Y);
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

void MapOBJ::on_mouseOut()
{
	if (tx)
	{
		tx->set_blendAlpha(alpha_mod_mouseOut);
	}
}

void MapOBJ::on_mouseOver()
{
	if (tx)
	{
		tx->set_blendAlpha(alpha_mod_mouseOver);
	}
}
