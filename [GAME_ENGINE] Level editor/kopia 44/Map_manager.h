#pragma once
#include "Map_states.h"
#include "Enemy_ID.h"
#include <string>
#include <SDL_render.h>
#include "Texture.h"

class Map_manager
{
public:
	static const Map_state & getMain_state() { return main_state; }

	static void Init();

	static const Selecting_Obj_state & getSelect_satate() { return select_state; }
	static const SDL_RendererFlip & get_OBJ_orient() { return object_flip; }
	static const OBJ_type & get_OBJ_type() { return object_type; }
	static const Map_Update_state & get_Update_state() { return update_state; }

	static void setMain_state(const Map_state & st);
	static void set_Update_state(Map_Update_state state);
	static void set_OBJ_orient(const Object_orient & ornt);
	static void set_OBJ_type(const OBJ_type & type);
	static void setSelect_state(const Selecting_Obj_state & st);

	static void reset_UpdateState();

	static void switch_OBJ_orient();

	static void set_EnemyID(const Enemy_ID & en_id);
	static const Enemy_ID & get_EnemyID() { return current_enemyID; }

	static void set_Background_name(const std::string & bg);
	static const std::string & get_Background_name() { return bg_name; }

	static void set_PlacingEnemy_state(Enemy_ID id, Texture * tX);

	static void render_tempOBJ();

	static const int get_editW() { return edit_W; }
	static const int get_editH() { return edit_H; }

	static const int get_mapBG_W() { return mapBG_W; }
	static const int get_mapBG_H() { return mapBG_H; }

	static const int get_tempRenderW() { return temp_renderOBJ.w; }
	static const int get_tempRenderH() { return temp_renderOBJ.h; }

	static void set_edit_area(int w, int h);

	static void update_mapBG(int w, int h);

	static void reset();

	static void switch_to_prev_state();

	static void Update_OBJ_sizes();
private:
	static Map_state prev_main_state;
	static Map_state main_state;

	static Map_Update_state update_state;

	static int edit_W, edit_H;

	static Selecting_Obj_state select_state;
	static OBJ_type object_type;

	static int mapBG_W, mapBG_H;

	static SDL_Rect temp_renderOBJ;

	static Object_orient object_orient;
	static SDL_RendererFlip object_flip;

	static Enemy_ID current_enemyID;

	static Texture * OBJ_texture;

	static std::string bg_name;
};