#include "Map_EditArea_manager.h"

Map_EditArea_state Map_EditArea_manager::main_state{ Map_EditArea_state::NONE };
Map_EditArea_state Map_EditArea_manager::prev_main_state{ Map_EditArea_state::NONE };

Selecting_Obj_state Map_EditArea_manager::select_state{ Selecting_Obj_state::NONE };
OBJ_type Map_EditArea_manager::object_type{ OBJ_type::NONE };
Object_orient Map_EditArea_manager::object_orient{ Object_orient::RIGHT };

SDL_RendererFlip Map_EditArea_manager::object_flip{ SDL_RendererFlip::SDL_FLIP_NONE };

Enemy_ID Map_EditArea_manager::current_enemyID{ Enemy_ID::NONE };

std::string Map_EditArea_manager::bg_name{};

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
		object_flip = SDL_FLIP_VERTICAL;
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