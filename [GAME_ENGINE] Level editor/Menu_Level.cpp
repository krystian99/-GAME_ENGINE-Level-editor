#include "Menu_Level.h"
#include "Engine_manager.h"
#include "LevelEditor_manager.h"
#include "Error.h"

Menu_Level::Menu_Level() :
	plansza{ {200, 100, 800, 800 }, "data/plansza.png"},
	kolko{ {300, 150, 200, 200 }, "data/kolko.png"}
{
	//data[0][0].set_position(300, 150, 200, 200);
}

void Menu_Level::events() // nie ma takiej potrzeby ¿eby tworzyæ specjalnych obiekty, skoro i tak s¹ tylko raz tworzone w tym miejscu i potrzebuj¹ wsparcia g³ównej klasy menu ¿eby wykonaæ dana czynnoœæ
{
	/*if (data[0][0].is_mouseKey_1hit(Mouse_key::L_BUTTON))
	{
		kolko.render();
	}*/

	/*input_levelName.events();
	input_mapName.events();

	input_area_level.events();
	input_area_map.events();

	if (input_levelName.is_mouseKey_1hit(Mouse_key::L_BUTTON))
	{
		input_area_level.setCurrent(true);
		input_area_map.setCurrent(false);

		input_mapName.getTX().reset_colorModulation();

		input_levelName.getTX().modulate_color(50, 50, 30);

		input_mapName.set_active(false);
		input_levelName.set_active(true);
	}
	else if (input_mapName.is_mouseKey_1hit(Mouse_key::L_BUTTON))
	{
		input_area_level.setCurrent(false);
		input_area_map.setCurrent(true);

		input_levelName.getTX().reset_colorModulation();

		input_mapName.getTX().modulate_color(50, 50, 30);

		input_mapName.set_active(true);
		input_levelName.set_active(false);
	}*/
}

void Menu_Level::events_indp()
{
	/*New.events();
	Load.events();

	if (New.is_mouseKey_1hit(Mouse_key::L_BUTTON) && !input_area_level.is_empty() && !input_area_map.is_empty()) {
		if (LevelEditor_manager::create_newLevel(input_area_level.getStr(), input_area_map.getStr()))
			Engine_manager::setState(Engine_state::IS_IN_LC);
	}
	else if (Load.is_mouseKey_1hit(Mouse_key::L_BUTTON) && !input_area_level.is_empty()) {
		if (LevelEditor_manager::loadLevel(input_area_level.getStr()))
			Engine_manager::setState(Engine_state::IS_IN_LC);
	}*/
}

void Menu_Level::render()
{
	plansza.render();

	/*currentMenu.render();

	level_nameInput_button.render();
	map_nameInput_button.render();

	input_levelName.render();
	input_mapName.render();

	input_area_level.render();
	input_area_map.render();

	New.render();
	Load.render();*/
}