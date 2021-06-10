#include "LevelCreator.h"
#include "Mouse.h"
#include "Video_Info.h"
#include "LevelEditor_manager.h"
#include "Renderer.h"
#include "Engine_manager.h"
#include "Menu_manager.h"
#include "Map_EditArea_manager.h"
#include "Folder_button.h"
#include "Buttons_OBJ_create.h"
#include "Buttons_Map_Functions.h"

LevelCreator::LevelCreator() : // inicjuje wszystkie dane Level Creatora - ustala funkcje przycisków itd.
	map_edit_area{ { 20, 100, 1050, 773 } },
	map_coordinate{ { 500, 30, 100, 50 } },
	mouse_cord{ { 700, 30, 100, 50 } },
	scrollBar_folders{ { 1089, 100, 80, 773 }, SDL_Color{ 255, 0, 0, 255 }, 70 },
	map_optionsBar{ { 20, 64, 500, 38 }, SDL_Color{ 0, 156, 125, 255 }, 50 }
{
	scrollBar_folders = {
		new Folder_button{ "Enemies", "data/textures/test.png", &Buttons_OBJ_create::Enemy::create_TEST },
		new Folder_button{ "Enemies", "data/textures/test2.png", &Buttons_OBJ_create::Enemy::create_TEST2 },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" }
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
}

// zdarzenia zale¿ne od myszki lub klawiatury
void LevelCreator::events()
{
	map_edit_area.events();

	localMenu_bar.events();

	scrollBar_folders.events();

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