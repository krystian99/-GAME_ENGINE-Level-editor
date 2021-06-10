#pragma once
#include "LevelEditor_state.h"
#include <string>
#include "Texture.h"
#include "Enemy_ID.h"
#include "OBJ_TYPES.h"

class LevelEditor_manager
{
public:
	static const LevelEditor_Main_state & get_Main_state() { return main_state; }
	static const LevelEditor_Management_state & get_Management_state() { return management_state; }

	static void set_Main_state(const LevelEditor_Main_state & st);
	static void set_Management_state(const LevelEditor_Management_state &st);

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

	static void switch_to_previousState();
private:
	static LevelEditor_Main_state main_state;
	static LevelEditor_Main_state main_previous_state;

	static LevelEditor_Management_state management_state;

	static std::string level_name;
	static std::string backgraound_name;

	static std::string levels_path;

	static std::string levels_mapsPath;
};