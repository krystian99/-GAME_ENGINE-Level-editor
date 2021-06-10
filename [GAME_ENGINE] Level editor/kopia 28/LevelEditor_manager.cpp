#include "LevelEditor_manager.h"
#include <fstream>

std::string LevelEditor_manager::levels_path{ "data/levels/saves/" };
std::string LevelEditor_manager::levels_mapsPath{ "data/levels/" };

Texture * LevelEditor_manager::currentTX{ nullptr };

LevelEditor_state LevelEditor_manager::state{};
LevelEditor_state LevelEditor_manager::previous_state{};

std::string LevelEditor_manager::level_name{};
std::string LevelEditor_manager::backgraound_name{};

Enemy_ID LevelEditor_manager::current_enemyID{ Enemy_ID::NONE };
BlockID LevelEditor_manager::current_blockID{ BlockID::NONE };
Others_ID LevelEditor_manager::current_OtherID{ Others_ID::NONE };

OBJ_TYPES LevelEditor_manager::current_typeOfOBJ{ OBJ_TYPES::NONE };

SDL_RendererFlip  LevelEditor_manager::obj_orient{ SDL_FLIP_NONE };

bool LevelEditor_manager::loadLevel(const std::string & name)
{
	std::ifstream sprawdz;

	sprawdz.open(levels_path + name);
	if (!sprawdz.is_open())
		return false;
	else sprawdz.close();

	level_name = name;
	state = LevelEditor_state::LOAD_LEVEL;

	return true;
}

void LevelEditor_manager::saveLevel()
{
	state = LevelEditor_state::SAVE_CURRENT_LEVEL;
}

void LevelEditor_manager::saveLevel_As(const std::string & name)
{
	level_name = name;

	state = LevelEditor_state::SAVE_AS;
}

bool LevelEditor_manager::create_newLevel(const std::string & name, const std::string & background)
{
	std::ifstream sprawdz;

	sprawdz.open(levels_mapsPath + background + ".png");

	if (!sprawdz.is_open())
		return false;
	else sprawdz.close();

	level_name = name;
	backgraound_name = background;

	state = LevelEditor_state::CREATE_NEW_LEVEL;

	return true;
}

void LevelEditor_manager::reset()
{
	state = LevelEditor_state::NONE;
	obj_orient = SDL_FLIP_NONE;
}

void LevelEditor_manager::set_backgroundName(const std::string & name)
{
	backgraound_name = name;
}

void LevelEditor_manager::setPlacing_state(OBJ_TYPES type, Texture * texture)
{
	currentTX = texture;
	current_typeOfOBJ = type;
	state = LevelEditor_state::SET_TEMP_OBJ;
}

void LevelEditor_manager::switch_objOrient()
{
	if (obj_orient == SDL_FLIP_NONE)
		obj_orient = SDL_FLIP_HORIZONTAL;
	else obj_orient = SDL_FLIP_NONE;
}

void LevelEditor_manager::setPlacing_state_asENEMY(Enemy_ID id)
{
	current_enemyID = id;
}

void LevelEditor_manager::setPlacing_state_asBLOCK(BlockID id)
{
	current_blockID = id;
}

void LevelEditor_manager::setPlacing_state_asOTHERS(Others_ID id)
{
	current_OtherID = id;
}

void LevelEditor_manager::setSate(const LevelEditor_state & st)
{
	previous_state = state;
	state = st;
}

void LevelEditor_manager::switch_to_previousState()
{
	state = previous_state;
}