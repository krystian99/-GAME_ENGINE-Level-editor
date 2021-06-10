#include "LevelCreator.h"
#include "Mouse.h"
#include "Video_Info.h"
#include "LevelEditor_manager.h"
#include "Renderer.h"
#include "Engine_manager.h"
#include "Menu_manager.h"
#include "Map_EditArea_manager.h"

LevelCreator::LevelCreator() :
	button_enemyPlace_test{ Enemy_ID::TEST,{ 1000, 10, 50, 50 } },
	l_buttonPressing{ false },
	map_coordinate{ { 500, 30, 100, 50 } },
	mouse_cord{ { 700, 30, 100, 50 } }
{
	buttons_mapOptions_bar.reserve(2);

	//map_coordinate.set(&map_edit_area.get_position(), &map_edit_area.get_backgroundArea()); // zamiana stanu na other

	buttons_mapOptions_bar = {
		new Button{ { 20, 67, 63, 35 }, "data/engine_files/single_object_selecting.png" },
		new Button{ { 83, 67, 63, 35 }, "data/engine_files/multi_object_selecting.png" }
	};
}

// zdarzenia zale¿ne od myszki lub klawiatury
void LevelCreator::events()
{
	map_edit_area.events();

	localMenu_bar.events();

	button_enemyPlace_test.events();
}

void LevelCreator::events_indp()
{
	if (map_edit_area.is_mouseOver())
		map_coordinate.events();

	mouse_cord.events();

	switch_Main_state();
	switch_Management_state();
}

void LevelCreator::render()
{
	if (LevelEditor_manager::get_Management_state() != LevelEditor_Management_state::CREATE_NEW_LEVEL && LevelEditor_manager::get_Management_state() != LevelEditor_Management_state::LOAD_LEVEL) {
		//for (auto & bt : buttons_mapOptions_bar)
		//bt->render();
		map_edit_area.render();

		button_enemyPlace_test.render();
		if (map_edit_area.is_mouseOver())
			map_coordinate.render();
		mouse_cord.render();
		localMenu_bar.render();
	}
}

void LevelCreator::load_Level()
{
	map_edit_area.load_Objects(LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName());
	map_coordinate.set(&map_edit_area.get_position(), &map_edit_area.get_backgroundArea()); // zamiana stanu na other
}

void LevelCreator::new_Level()
{
	map_edit_area.reset();
	map_edit_area.set_background(LevelEditor_manager::get_levels_mapsPath() + LevelEditor_manager::get_backgroundName() + ".png");
	map_coordinate.set(&map_edit_area.get_position(), &map_edit_area.get_backgroundArea()); // zamiana stanu na other
}

void LevelCreator::switch_Main_state()
{
	switch (LevelEditor_manager::get_Main_state()) {
	case LevelEditor_Main_state::IS_EDITING_LEVEL:
		map_edit_area.events_indp();
		break;
	case LevelEditor_Main_state::IS_IN_LOCAL_MENU:
		localMenu_bar.events_indp();
		break;
	}
}

void LevelCreator::switch_Management_state()
{
	switch (LevelEditor_manager::get_Management_state())
	{
	case LevelEditor_Management_state::CREATE_NEW_LEVEL:
		new_Level();
		LevelEditor_manager::reset();
		localMenu_bar.reset();
		map_edit_area.reset();
		break;
	case LevelEditor_Management_state::LOAD_LEVEL:
		load_Level();
		LevelEditor_manager::reset();
		localMenu_bar.reset();
		break;
	case LevelEditor_Management_state::SAVE_CURRENT_LEVEL: // zapisz pod nazw¹ wprowadzon¹ poczas wpisywania nazwy na samym pocz¹tku
		save_level(); // zapisz pod nazw¹ któr¹ podawano przy ³adowaniu/tworzeniu levela
		LevelEditor_manager::switch_to_previousState(); // przywróæ poprzedni stan
		break;
	case LevelEditor_Management_state::SAVE_AS: // Zapisz pod inn¹ nazw¹
		save_level();
		LevelEditor_manager::switch_to_previousState(); // przywróæ poprzedni stan
		break;
	}
}

void LevelCreator::save_level()
{
	map_edit_area.save_Objects(LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName());
}