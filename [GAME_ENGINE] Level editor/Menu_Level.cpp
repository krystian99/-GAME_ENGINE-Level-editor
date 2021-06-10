#include "Menu_Level.h"
#include "Engine_manager.h"
#include "LevelEditor_manager.h"
#include "Error.h"

Menu_Level::Menu_Level() :
	currentMenu{ { 400, 30, 400, 50 }, "data/menus/level_editor/LEVEL.png" },
	level_nameInput_button{ { 485, 220, 200, 50 }, "data/menus/level_editor/LEVELNAME.png" },
	map_nameInput_button{ { 485, 400, 200, 50 }, "data/menus/level_editor/MAPNAME.png" },
	input_levelName{ "data/menus/level_editor/INPUT BUTTON.png" },
	input_mapName{ "data/menus/level_editor/INPUT BUTTON.png" },
	input_area_level{ { 360, 290, 480, 50 }, 365, 287, "data/fonts/standard_font.ttf", 50, { 0, 0, 45 } },
	input_area_map{ { 360, 470, 480, 50 }, 365, 467, "data/fonts/standard_font.ttf", 50, { 0, 0, 45 } },
	New{ { 350, 641, 500, 70 }, "data/menus/level_editor/NEW.png" },
	Load{ { 350, 735, 500, 70 }, "data/menus/level_editor/LOAD.png" }
{
	input_levelName.set_scaled_position({ 350, 280, 500, 70 });
	input_mapName.set_scaled_position({ 350, 460, 500, 70 });
}

void Menu_Level::events() // nie ma takiej potrzeby ¿eby tworzyæ specjalnych obiekty, skoro i tak s¹ tylko raz tworzone w tym miejscu i potrzebuj¹ wsparcia g³ównej klasy menu ¿eby wykonaæ dana czynnoœæ
{
	input_levelName.events();
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
	}
}

void Menu_Level::events_indp()
{
	New.events();
	Load.events();

	if (New.is_mouseKey_1hit(Mouse_key::L_BUTTON) && !input_area_level.is_empty() && !input_area_map.is_empty()) {
		if (LevelEditor_manager::create_newLevel(input_area_level.getStr(), input_area_map.getStr()))
			Engine_manager::setState(Engine_state::IS_IN_LC);
	}
	else if (Load.is_mouseKey_1hit(Mouse_key::L_BUTTON) && !input_area_level.is_empty()) {
		if (LevelEditor_manager::loadLevel(input_area_level.getStr()))
			Engine_manager::setState(Engine_state::IS_IN_LC);
	}
}

void Menu_Level::render()
{
	currentMenu.render();

	level_nameInput_button.render();
	map_nameInput_button.render();

	input_levelName.render();
	input_mapName.render();

	input_area_level.render();
	input_area_map.render();

	New.render();
	Load.render();
}