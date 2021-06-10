#include "LevelEditor_manager.h"
#include <fstream>

std::string LevelEditor_manager::levels_path{ "data/levels/saves/" };
std::string LevelEditor_manager::levels_mapsPath{ "data/levels/" };

LevelEditor_Main_state LevelEditor_manager::main_state{ LevelEditor_Main_state::IS_EDITING_LEVEL };
LevelEditor_Main_state LevelEditor_manager::main_previous_state{ LevelEditor_Main_state::NONE };

LevelEditor_Management_state LevelEditor_manager::management_state{ LevelEditor_Management_state::NONE };

std::string LevelEditor_manager::level_name{};
std::string LevelEditor_manager::backgraound_name{};

void LevelEditor_manager::set_Main_state(const LevelEditor_Main_state & st)
{
	main_previous_state = main_state;
	main_state = st;
}

void LevelEditor_manager::set_Management_state(const LevelEditor_Management_state & st)
{
	management_state = st;
}

bool LevelEditor_manager::loadLevel(const std::string & name)
{
	std::ifstream sprawdz;

	sprawdz.open(levels_path + name);
	if (!sprawdz.is_open())
		return false;
	else sprawdz.close();

	level_name = name;
	management_state = LevelEditor_Management_state::LOAD_LEVEL;

	return true;
}

void LevelEditor_manager::saveLevel()
{
	management_state = LevelEditor_Management_state::SAVE_CURRENT_LEVEL;
}

void LevelEditor_manager::saveLevel_As(const std::string & name)
{
	level_name = name;

	management_state = LevelEditor_Management_state::SAVE_AS;
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

	management_state = LevelEditor_Management_state::CREATE_NEW_LEVEL;

	return true;
}

void LevelEditor_manager::reset()
{
	main_state = LevelEditor_Main_state::IS_EDITING_LEVEL;
	management_state = LevelEditor_Management_state::NONE;
}

void LevelEditor_manager::set_backgroundName(const std::string & name)
{
	backgraound_name = name;
}

void LevelEditor_manager::switch_to_previousState()
{
	main_state = main_previous_state;
}