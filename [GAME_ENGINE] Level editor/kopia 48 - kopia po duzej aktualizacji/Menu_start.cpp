#include "Menu_start.h"
#include "Menu_manager.h"
#include "Video_Info.h"

Menu_start::Menu_start() :
	level_menu{ { (Video_Info::getWindow_W() / 2 - 90), 70, 180, 70 }, Video_Info::getWindow_W() / 2 - 80, 72, "data/fonts/standard_font.ttf", "Level Menu", 50, { 0, 255 } },
	anim_menu{ { (Video_Info::getWindow_W() / 2 - 90), 200, 180, 70 }, Video_Info::getWindow_W() / 2 - 80, 202, "data/fonts/standard_font.ttf", "Anim Menu", 50, { 0, 255 } }
{}

void Menu_start::events()
{
	level_menu.events();
	anim_menu.events();

	if (level_menu.is_mouseKey_1hit(Mouse_key::L_BUTTON))
		Menu_manager::set_Menu(Menu_ID::LEVEL_MENU);
	else if (anim_menu.is_mouseKey_1hit(Mouse_key::L_BUTTON))
		Menu_manager::set_Menu(Menu_ID::ANIMATION_MENU);
}

void Menu_start::events_indp()
{

}

void Menu_start::render()
{
	level_menu.render();
	anim_menu.render();
}