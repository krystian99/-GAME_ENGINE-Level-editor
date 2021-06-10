#pragma once
#include "Map_EditArea_state.h"
#include "Enemy_ID.h"
#include <string>
#include <SDL_render.h>

class Map_EditArea_manager
{
public:
	static const Map_EditArea_state & getMain_state() { return main_state; }

	static const Selecting_Obj_state & getSelect_satate() { return select_state; }
	static const SDL_RendererFlip & get_OBJ_orient() { return object_flip; }
	static const OBJ_type & get_OBJ_type() { return object_type; }

	static void setMain_state(const Map_EditArea_state & st);

	static void set_OBJ_orient(const Object_orient & ornt);
	static void set_OBJ_type(const OBJ_type & type);
	static void setSelect_state(const Selecting_Obj_state & st);

	static void switch_OBJ_orient();

	static void set_EnemyID(const Enemy_ID & en_id);
	static const Enemy_ID & get_EnemyID() { return current_enemyID; }

	static void set_Background_name(const std::string & bg);
	static const std::string & get_Background_name() { return bg_name; }

	static void reset();

	static void switch_to_prev_state();
private:
	static Map_EditArea_state prev_main_state;
	static Map_EditArea_state main_state;

	static Selecting_Obj_state select_state;
	static OBJ_type object_type;

	static Object_orient object_orient;
	static SDL_RendererFlip object_flip;

	static Enemy_ID current_enemyID;

	static std::string bg_name;
};