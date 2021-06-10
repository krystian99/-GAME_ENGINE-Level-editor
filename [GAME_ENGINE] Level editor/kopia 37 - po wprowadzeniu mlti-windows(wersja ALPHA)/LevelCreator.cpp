#include "LevelCreator.h"
#include "LevelEditor_manager.h"
#include "Menu_manager.h"
#include "Map_EditArea_manager.h"
#include "Folder_button.h"
#include "Buttons_OBJ_create.h"
#include "Buttons_Map_Functions.h"

LevelCreator::LevelCreator() : // inicjuje wszystkie dane Level Creatora - ustala funkcje przycisk�w itd.
	map_edit_area{ { 115, 141, 960, 750 } },
	map_coordinate{ { 300, 40, 100, 50 } },
	mouse_cord{ { 115, 40, 100, 50 } },
	scrollBar_folders{ { 1089, 141, 80, 750 }, SDL_Color{ 60, 60, 60, 255 }, 80 },
	map_optionsBar{ { 115, 90, 500, 38 }, SDL_Color{ 0, 156, 125, 255 }, 55 },
	menu_options{ { 5, 141, 105, 40 }, "data/local_menus/Options/Options.png", true, 40 },
	Level_name{ 130, 15, "data/fonts/standard_font.ttf", 30, { 255, 255, 255, 255 } },
	Map_name{ 400, 15, "data/fonts/standard_font.ttf", 30, { 255, 255, 255, 255 } },
	window_createTest{ { 674, 42, 50, 30 }, "data/test.png" }
{
	scrollBar_folders = {
		new Folder_button{ "Enemies", "data/textures/test.png", &Buttons_OBJ_create::Enemy::create_TEST },
		new Folder_button{ "Enemies", "data/textures/test2.png", &Buttons_OBJ_create::Enemy::create_TEST2 },
		new Folder_button{ "Enemies", "data/textures/test3.png", &Buttons_OBJ_create::Enemy::create_TEST3 },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/textures/test3.png", &Buttons_OBJ_create::Enemy::create_TEST3 }
	};

	map_optionsBar = {
		new Button{ "data/engine_files/single_object_selecting.png", &Buttons_Map_Functions::onClick::single_select_button },
		new Button{ "data/engine_files/multi_object_selecting.png", &Buttons_Map_Functions::onClick::multi_select_button },
		new Button{ "data/engine_files/delete.png",  &Buttons_Map_Functions::onClick::delete_button },
		new Button{ "data/engine_files/map_move.png", &Buttons_Map_Functions::onClick::moveMap_button },
		// teraz dla testow
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" }
		// koniec testow
	};

	menu_options = {
		new Button{ "data/local_menus/Options/SAVE.png" },
		new Button{ "data/local_menus/Options/SAVE_AS.png" },
		new Button{ "data/local_menus/Options/LOAD.png" },
		new Button{ "data/local_menus/Options/EXIT.png" },
	};
}

void LevelCreator::events_multiwindow_test()
{
	window_createTest.events();
}

// zdarzenia zale�ne od myszki lub klawiatury
void LevelCreator::events()
{
	map_edit_area.events();

	localMenu_bar.events();

	menu_options.events();

	scrollBar_folders.events();

	window_createTest.events();

	map_optionsBar.events();
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
	scrollBar_folders.render();
	map_optionsBar.render();

	map_edit_area.render();

	menu_options.render();

	Level_name.render();
	Map_name.render();

	window_createTest.render();

	if (map_edit_area.is_mouseOver())
		map_coordinate.render();
	mouse_cord.render();
	localMenu_bar.render();
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

		Level_name.update("LEVEL:   " + LevelEditor_manager::get_levelName());
		Map_name.update("MAP:   " + LevelEditor_manager::get_backgroundName());
		break;
	case LevelEditor_Management_state::LOAD_LEVEL:
		load_Level();
		LevelEditor_manager::reset();
		localMenu_bar.reset();

		Level_name.update("LEVEL:   " + LevelEditor_manager::get_levelName());
		Map_name.update("MAP:   " + LevelEditor_manager::get_backgroundName());
		break;
	case LevelEditor_Management_state::SAVE_CURRENT_LEVEL: // zapisz pod nazw� wprowadzon� poczas wpisywania nazwy na samym pocz�tku
		save_level(); // zapisz pod nazw� kt�r� podawano przy �adowaniu/tworzeniu levela
		LevelEditor_manager::switch_to_previousState(); // przywr�� poprzedni stan
		break;
	case LevelEditor_Management_state::SAVE_AS: // Zapisz pod inn� nazw�
		save_level();
		LevelEditor_manager::switch_to_previousState(); // przywr�� poprzedni stan
		break;
	}
}

void LevelCreator::save_level()
{
	map_edit_area.save_Objects(LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName());
}