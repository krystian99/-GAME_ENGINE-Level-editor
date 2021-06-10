#include "MenuLocal_func.h"
#include "LevelEditor_manager.h"
#include "Engine_manager.h"

void MenuLocal_functions::Menu_options::button_Save()
{
	LevelEditor_manager::saveLevel();
}

void MenuLocal_functions::Menu_options::button_SaveAs(const char * str)
{
	LevelEditor_manager::saveLevel_As(str);
}

bool MenuLocal_functions::Menu_options::button_Load(const char * str)
{
	return LevelEditor_manager::loadLevel(str);
}

void MenuLocal_functions::Menu_options::button_Exit()
{
	Engine_manager::Quit();
}