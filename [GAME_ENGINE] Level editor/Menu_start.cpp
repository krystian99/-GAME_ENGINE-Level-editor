#include "Menu_start.h"
#include "Menu_manager.h"
#include "Video_Info.h"
#include "Engine_manager.h"
#include "Mouse.h"

Menu_start::Menu_start() :
	project_name{ { 370, 30, 500, 120 } ,"data/menus/start/PV.png" },
	start_game{ { 400, 280, 400, 50 }, "data/start_game.png" },
	animationsEditor_button{ { 370, 390, 480, 50 }, "data/menus/start/ANIM.png" },
	Script_editor_button{ { 400, 490, 400, 50 }, "data/menus/start/SCRIPT.png" },
	Exit{ { 1040, 850, 120, 50 }, "data/menus/start/EXIT.png" },
	copyright{ 50, 800, "data/fonts/standard_font.ttf", "Silnik graficzny stworzony przez: Krystian Sarnecki ;)", 25, { 200, 120, 50, 255 } }
{}

void Menu_start::events()
{
	start_game.events();
	animationsEditor_button.events();
	Script_editor_button.events();
	Exit.events();

	if (start_game.is_mouseKey_1hit(Mouse_key::L_BUTTON)) {
		//Engine_manager::setState(Engine_state::IS_IN_LC);
		Menu_manager::set_Menu(Menu_ID::LEVEL_MENU);
	}
	else if (Exit.is_mouseKey_1hit(Mouse_key::L_BUTTON))
		Engine_manager::Quit();
	else if (animationsEditor_button.is_mouseKey_1hit(Mouse_key::L_BUTTON)) // jak na razie wy³¹czone, bo jest niedopracowane
		Menu_manager::set_Menu(Menu_ID::ANIMATION_MENU);
}

void Menu_start::events_indp()
{

}

void Menu_start::render()
{
	Exit.render();
	project_name.render();

	copyright.render();

	start_game.render();
	animationsEditor_button.render();
	Script_editor_button.render();
}