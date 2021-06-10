#include "Menu_localEditor.h"
#include "Menu_localEditor_manager.h"

Menu_localEditor::Menu_localEditor() :
	menu_level{ { 20, 5, 80, 26 }, 35, 2, "data/fonts/standard_font.ttf", "LEVEL", 25, { 255 } }
{}

void Menu_localEditor::events() // zale¿ne od myszki lub klawiatury
{
	menu_level.events();
	/*switch (Menu_localEditor_manager::getState())
	{
	case Menu_localEditor_state::IS_IN_LEVEL_MENU:
		menu_level.events();
		break;
	case Menu_localEditor_state::IS_IN_OBJECS_MENU:
		break;
	}*/
}

void Menu_localEditor::events_indp()
{

}

void Menu_localEditor::render() // ca³kowicie niezale¿ne od myszki i innych zdarzeñ
{
	menu_level.render();
	/*switch (Menu_localEditor_manager::getState())
	{
	case Menu_localEditor_state::IS_IN_LEVEL_MENU:
		menu_level.render();
		break;
	case Menu_localEditor_state::IS_IN_OBJECS_MENU:
		break;
	}*/
}

void Menu_localEditor::reset()
{
	menu_level.reset();
}