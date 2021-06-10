#pragma once
#include <string>

enum class AnimConfig_state {  };
enum class AnimConfig_mngState { NONE, NEW_CONFIG, LOAD_CONFIG };


class Animation_manager // zarz¹dza danymi statycznymi
{
public:
	static bool create_newConfig(const std::string & name, const std::string & frames);
	static bool load_Config(const std::string & name);

	static void set_mngState(AnimConfig_mngState state);

	static const AnimConfig_mngState & get_mngState() { return mngState; }

	static const std::string & get_animName() { return anim_Name; }
	static const std::string & get_animPath() { return anim_path; }

	static const int & get_framesDigit() { return amountOf_Frames; }

	//static void switch_to_previousState();

private:
	static AnimConfig_mngState mngState;

	static std::string anim_path;
	static std::string anim_config_path;

	static std::string anim_Name;
	static int amountOf_Frames;
};