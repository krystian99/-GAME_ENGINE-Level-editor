#include "LevelCreator.h"
#include "Mouse.h"
#include "Video_Info.h"

static const std::string levels_save_path = "data/levels/saves/";

void LevelCreator::Init()
{

}

void LevelCreator::load_Level(const std::string & level)
{
	using std::ios_base;

	clear_map();

	level_name = level;
	load.open((levels_save_path + level).c_str(), ios_base::in | ios_base::binary);

	if (load.is_open()) {
		while (load.read(reinterpret_cast<char*>(&enemy_data), sizeof(Enemy_data)))
			create_EnemyOBJ(enemy_data.map_x, enemy_data.map_y);
	}
	load.close();
}

void LevelCreator::new_Level(const std::string & level_name, const std::string & map_path)
{
	
}

void LevelCreator::events()
{

}

void LevelCreator::render()
{
	render_Map();
	render_Blocks();
	render_Enemies();
}

void LevelCreator::save_level()
{
	using std::ios_base;

	save.open((levels_save_path + level_name).c_str(), ios_base::out | ios_base::binary);

	if (save.is_open()) {
		for (auto & enemy : enemies)
			save.write(reinterpret_cast<const char*>(&enemy.getData()), sizeof(enemy.getData()));
	}
	save.close();
}

void LevelCreator::mouse_handler()
{

}

void LevelCreator::set_PlayerSpawn()
{

}

void LevelCreator::create_EnemyOBJ(const int & X, const int & Y)
{
	static int RenderPOS_X, RenderPOS_Y;
	static double scaleX, scaleY;

	scaleX = double(X - mapBG_area.area.x) / double(mapBG_area.area.w);
	scaleY = double(Y - mapBG_area.area.y) / double(mapBG_area.area.h);

	RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
	RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

	enemies.push_back({ X, Y }); // po³ó¿ obiekt wzglêdem textury mapy
	enemies.back().setRenderPos(RenderPOS_X, RenderPOS_Y);
}

void LevelCreator::clear_map()
{
	enemies.clear();
	blocks.clear();
}

void LevelCreator::setMap_view()
{
	static double scaleX, scale_recentX;
	static double scaleY, scale_recentY;

	static int pointX, point_recentX;

	static int maprender_absX, maprender_absY;

	if (Mouse::getX() < Mouse::getR_x() || Mouse::getX() > Mouse::getR_x()
		|| Mouse::getY() < Mouse::getR_y() || Mouse::getY() > Mouse::getY())
	{
		scaleX = double(Mouse::getX() - edit_area.x) / double(edit_area.w);
		scale_recentX = double(Mouse::getR_x() - edit_area.x) / double(edit_area.w);

		pointX = mapBG_area.area.x + round(mapBG_area.area.w * scaleX);
		point_recentX = mapBG_area.area.x + round(mapBG_area.area.w * scale_recentX);

		maprender_absX = abs(pointX - point_recentX);

		if (Mouse::getX() < Mouse::getR_x() && mapBG_area.canMove_r(mapBG)) {
			if (mapBG_area.area.x + maprender_absX + mapBG_area.area.w < mapBG.getWidth())
				mapBG_area.area.x += maprender_absX;
			else
				mapBG_area.area.x = mapBG.getWidth() - mapBG_area.area.w;
		}
		else if (Mouse::getX() > Mouse::getR_x() && mapBG_area.canMove_l()) {

			if (mapBG_area.area.x - maprender_absX > 0)
				mapBG_area.area.x -= maprender_absX;
			else
				mapBG_area.area.x = 0;
		}

		for (auto & enemy : enemies) {
			static int RenderPOS_X, RenderPOS_Y;

			scaleX = double(enemy.getX() - mapBG_area.area.x) / double(mapBG_area.area.w);
			scaleY = double(enemy.getY() - mapBG_area.area.y) / double(mapBG_area.area.h);

			RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
			RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

			enemy.setRenderPos(RenderPOS_X, RenderPOS_Y);
		}
	}
}

void LevelCreator::render_Map()
{
	mapBG.render(&mapBG_area.area, &edit_area);
}

void LevelCreator::render_Enemies()
{
	for (auto & enemy : enemies)
		enemy.render();
}

void LevelCreator::render_Blocks()
{
	for (auto & block : blocks)
		block.render();
}

bool LevelCreator::Map_area::canMove_r(const Texture & TX)
{
	if (area.x + area.w < TX.getWidth())
		return true;
	return false;
}

bool LevelCreator::Map_area::canMove_l()
{
	if (area.x > 0)
		return true;
	return false;
}

bool LevelCreator::Map_area::canMove_u()
{
	if (area.y > 0)
		return true;
	return false;
}

bool LevelCreator::Map_area::canMove_d(const Texture & TX)
{
	if (area.y + area.h > TX.getHeight())
		return true;
	return false;
}