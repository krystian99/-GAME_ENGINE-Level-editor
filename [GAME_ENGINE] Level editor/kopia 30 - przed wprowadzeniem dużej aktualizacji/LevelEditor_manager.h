#pragma once
#include "LevelEditor_state.h"
#include <string>
#include "Texture.h"
#include "Enemy_ID.h"
#include "OBJ_TYPES.h"
#include "BLOCK_ID.h"
#include "Others_ID.h"

class LevelEditor_manager
{
public:
	static const LevelEditor_state & getState() { return state; }

	static bool loadLevel(const std::string & name);
	static void saveLevel();
	static void saveLevel_As(const std::string & name);
	static bool create_newLevel(const std::string & name, const std::string & background);

	static const std::string & get_levelName() { return level_name; }

	static const std::string & get_levelsPath() { return levels_path; }
	static const std::string & get_levels_mapsPath() { return levels_mapsPath; }

	static void reset();

	static const std::string & get_backgroundName() { return backgraound_name; }
	static void set_backgroundName(const std::string & name);

	static void setPlacing_state(OBJ_TYPES type, Texture * texture);

	static const SDL_RendererFlip & getOBJ_orient() { return obj_orient; }
	static void switch_objOrient();

	static void setPlacing_state_asENEMY(Enemy_ID id);
	static void setPlacing_state_asBLOCK(BlockID id);
	static void setPlacing_state_asOTHERS(Others_ID id);

	static const OBJ_TYPES & getType_OBJ() { return current_typeOfOBJ; }
	static const Enemy_ID & getEnemy_ID() { return current_enemyID; }
	static const BlockID & getBlock_ID() { return current_blockID; }
	//static const  & getEnemy_ID() { return current_enemyID; }

	static Texture * getCurrentTX() { return currentTX; }

	static void setSate(const LevelEditor_state & st);
	static void switch_to_previousState();
private:
	static LevelEditor_state state;
	static LevelEditor_state previous_state;

	static std::string level_name;
	static std::string backgraound_name;

	static std::string levels_path;

	static Enemy_ID current_enemyID;
	static BlockID current_blockID;
	static Others_ID current_OtherID;
	static OBJ_TYPES current_typeOfOBJ;

	static Texture * currentTX;

	static SDL_RendererFlip obj_orient;

	static std::string levels_mapsPath;
};