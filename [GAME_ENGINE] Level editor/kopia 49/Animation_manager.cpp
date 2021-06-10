#include "Animation_manager.h"
#include <fstream>

AnimConfig_mngState Animation_manager::mngState{ AnimConfig_mngState::NONE };

std::string Animation_manager::anim_path{ "data/animations/" };
std::string Animation_manager::anim_config_path{ "data/animations/configs/" };

std::string Animation_manager::anim_Name{};
int Animation_manager::amountOf_Frames{ 0 };

bool Animation_manager::create_newConfig(const std::string & name, const std::string & frames)
{
	std::ifstream sprawdz;

	sprawdz.open(anim_path + name + ".png");
	if (!sprawdz.is_open())
		return false;
	else sprawdz.close();

	amountOf_Frames = std::stoi(frames);

	anim_Name = name;
	mngState = AnimConfig_mngState::NEW_CONFIG;

	return true;
}

bool Animation_manager::load_Config(const std::string & name)
{
	std::ifstream sprawdz;

	sprawdz.open(anim_config_path + name);
	if (!sprawdz.is_open())
		return false;
	else sprawdz.close();

	anim_Name = name;
	mngState = AnimConfig_mngState::LOAD_CONFIG;

	return true;
}

void Animation_manager::set_mngState(AnimConfig_mngState state)
{
	mngState = state;
}