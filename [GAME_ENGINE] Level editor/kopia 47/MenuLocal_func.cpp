#include "MenuLocal_func.h"
#include "LevelEditor_manager.h"
#include "Engine_manager.h"

void MenuLocal_functions::Menu_options::button_Save()
{
	LevelEditor_manager::saveLevel();
}

bool MenuLocal_functions::Menu_options::button_SaveAs(std::string str)
{
	LevelEditor_manager::saveLevel_As(str);
	return true;
}

bool MenuLocal_functions::Menu_options::button_Load(std::string str)
{
	return LevelEditor_manager::loadLevel(str);
}

void MenuLocal_functions::Menu_options::button_Exit()
{
	Engine_manager::Quit();
}