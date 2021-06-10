#include "Map_EditArea_manager.h"
#include "Mouse.h"
#include "Enemy_Types.h"

Map_EditArea_state Map_EditArea_manager::main_state{ Map_EditArea_state::NONE };
Map_EditArea_state Map_EditArea_manager::prev_main_state{ Map_EditArea_state::NONE };

Selecting_Obj_state Map_EditArea_manager::select_state{ Selecting_Obj_state::NONE };
OBJ_type Map_EditArea_manager::object_type{ OBJ_type::NONE };
Object_orient Map_EditArea_manager::object_orient{ Object_orient::RIGHT };

SDL_RendererFlip Map_EditArea_manager::object_flip{ SDL_RendererFlip::SDL_FLIP_NONE };

Enemy_ID Map_EditArea_manager::current_enemyID{ Enemy_ID::NONE };

SDL_Rect Map_EditArea_manager::temp_renderOBJ{};

Texture * Map_EditArea_manager::OBJ_texture{ nullptr };

std::string Map_EditArea_manager::bg_name{};

int Map_EditArea_manager::edit_W{};
int Map_EditArea_manager::edit_H{};

int Map_EditArea_manager::mapBG_W{};
int Map_EditArea_manager::mapBG_H{};

void Map_EditArea_manager::setMain_state(const Map_EditArea_state & st)
{
	prev_main_state = main_state;
	main_state = st;
}

void Map_EditArea_manager::set_OBJ_orient(const Object_orient & ornt)
{
	object_orient = ornt;
}

void Map_EditArea_manager::set_OBJ_type(const OBJ_type & type)
{
	object_type = type;
}

void Map_EditArea_manager::setSelect_state(const Selecting_Obj_state & st)
{
	select_state = st;
}

void Map_EditArea_manager::switch_OBJ_orient()
{
	if (object_orient == Object_orient::RIGHT) {
		object_orient = Object_orient::LEFT;
		object_flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		object_flip = SDL_FLIP_NONE;
		object_orient = Object_orient::RIGHT;
	}
}

void Map_EditArea_manager::set_EnemyID(const Enemy_ID & en_id)
{
	current_enemyID = en_id;
}

void Map_EditArea_manager::set_Background_name(const std::string & bg)
{
	bg_name = bg;
}

void Map_EditArea_manager::set_PlacingEnemy_state(Enemy_ID id, Texture * tX)
{
	main_state = Map_EditArea_state::PLACING_OBJECTS;
	object_type = OBJ_type::ENEMY;
	current_enemyID = id;
	OBJ_texture = tX;

	set_temp_renderOBJ();
}

void Map_EditArea_manager::set_temp_renderOBJ()
{
	static double scaleX, scaleY;

	using namespace Enemy_Types;
	switch (get_OBJ_type()) {
	case OBJ_type::ENEMY:
		switch (get_EnemyID()) {
		case Enemy_ID::TEST:
			scaleX = std::round(Enemy_Test::getW() * Base_OBJ::get_multiplier()) / double(Map_EditArea_manager::get_mapBG_W());
			scaleY = std::round(Enemy_Test::getH() * Base_OBJ::get_multiplier()) / double(Map_EditArea_manager::get_mapBG_H());

			temp_renderOBJ.w = round(scaleX * Map_EditArea_manager::get_editW());
			temp_renderOBJ.h = round(scaleY * Map_EditArea_manager::get_editH());
			break;
		case Enemy_ID::TEST2:
			scaleX = std::round(Enemy_Test2::getW() * Base_OBJ::get_multiplier()) / double(Map_EditArea_manager::get_mapBG_W());
			scaleY = std::round(Enemy_Test2::getH() * Base_OBJ::get_multiplier()) / double(Map_EditArea_manager::get_mapBG_H());

			temp_renderOBJ.w = round(scaleX * Map_EditArea_manager::get_editW());
			temp_renderOBJ.h = round(scaleY * Map_EditArea_manager::get_editH());
			break;
		case Enemy_ID::TEST3:
			scaleX = std::round(Enemy_Test3::getW() * Base_OBJ::get_multiplier()) / double(Map_EditArea_manager::get_mapBG_W());
			scaleY = std::round(Enemy_Test3::getH() * Base_OBJ::get_multiplier()) / double(Map_EditArea_manager::get_mapBG_H());

			temp_renderOBJ.w = round(scaleX * Map_EditArea_manager::get_editW());
			temp_renderOBJ.h = round(scaleY * Map_EditArea_manager::get_editH());
			break;
		}
	case OBJ_type::PLAYER:
		break;
	}
}

void Map_EditArea_manager::update_mapBG(int w, int h)
{
	mapBG_W = w;
	mapBG_H = h;
}

void Map_EditArea_manager::render_tempOBJ()
{
	static const int & mX = Mouse::getX();
	static const int & mY = Mouse::getY();

	temp_renderOBJ.x = mX;
	temp_renderOBJ.y = mY;

	OBJ_texture->render(nullptr, &temp_renderOBJ, object_flip);
}

void Map_EditArea_manager::set_edit_area(int w, int h)
{
	edit_W = w;
	edit_H = h;
}

void Map_EditArea_manager::reset()
{
	object_orient = Object_orient::RIGHT;
	current_enemyID = Enemy_ID::NONE;
	main_state = Map_EditArea_state::NONE;
	select_state = Selecting_Obj_state::NONE;
	object_type = OBJ_type::NONE;
}

void Map_EditArea_manager::switch_to_prev_state()
{
	main_state = prev_main_state;
	prev_main_state = Map_EditArea_state::NONE;
}