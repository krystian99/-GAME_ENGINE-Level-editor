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
	button_enemyPlace_test{ Enemy_ID::TEST,{ 1000, 10, 50, 50 } },
	l_buttonPressing{ false },
	map_coordinate{ { 500, 30, 100, 50 } },
	mouse_cord{ { 700, 30, 100, 50 } },
	single_selectOBJ{ { 20, 67, 63, 35 }, "data/engine_files/single_object_selecting.png" },
	multi_selectOBJ{ { 83, 67, 63, 35 }, "data/engine_files/multi_object_selecting.png" },
	delete_OBJ{ { 146, 67, 63, 35 }, "data/engine_files/delete.png" },
	mapMove{ { 209, 67, 63, 35 }, "data/engine_files/map_move.png" },
	scrollBar_folders{ { 1089, 100, 80, 773 }, SDL_Color{ 255, 0, 0, 255 } }
{
	scrollBar_folders = { // dla testów
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
		new Folder_button{ "Enemies", /*to trzeba zmienic - jest tutaj tylko dla testu*/"data/engine_files/test.png" },
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
}

// zdarzenia zale¿ne od myszki lub klawiatury
void LevelCreator::events()
{
	map_edit_area.events();

	localMenu_bar.events();

	scrollBar_folders.events();

	button_enemyPlace_test.events();
}

void LevelCreator::events_indp()
{
	if (map_edit_area.is_mouseOver())
		map_coordinate.events();

	mouse_cord.events();

	single_selectOBJ.events();
	multi_selectOBJ.events();
	delete_OBJ.events();
	mapMove.events();

	if (single_selectOBJ.is_clicked()) { // tego nie bêdzie - zostanie zast¹pione funkcj¹ z przestrzeni nazw, która bêdzie umieszona w konstruktorze
		Map_EditArea_manager::setMain_state(Map_EditArea_state::SELECTING_OBJECTS);
		Map_EditArea_manager::setSelect_state(Selecting_Obj_state::SINGLE);
	}
	else if (multi_selectOBJ.is_clicked()) {
		Map_EditArea_manager::setMain_state(Map_EditArea_state::SELECTING_OBJECTS);
		Map_EditArea_manager::setSelect_state(Selecting_Obj_state::MULTI);
	}
	else if (delete_OBJ.is_clicked()) {
		Map_EditArea_manager::setMain_state(Map_EditArea_state::DELETE_OBJECTS);
	}
	else if (mapMove.is_clicked()) {
		Map_EditArea_manager::setMain_state(Map_EditArea_state::MOVING_MAP);
	}

	switch_Main_state();
	switch_Management_state();
}

void LevelCreator::render()
{
	single_selectOBJ.render();
	multi_selectOBJ.render();
	delete_OBJ.render();
	mapMove.render();

	scrollBar_folders.render();

	map_edit_area.render();

	button_enemyPlace_test.render();
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