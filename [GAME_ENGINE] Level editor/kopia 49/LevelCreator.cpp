#include "LevelCreator.h"
#include "LevelEditor_manager.h"
#include "Menu_manager.h"
#include "Map_manager.h"
#include "Folder_button.h"
#include "Buttons_OBJ_create.h"
#include "Buttons_Map_Functions.h"
#include "MenuLocal_func.h"

LevelCreator::LevelCreator() : // inicjuje wszystkie dane Level Creatora - ustala funkcje przycisków itd.
	map_edit_area{ { 115, 141, 960, 750 } },
	map_coordinate{ { 300, 40, 100, 50 } },
	mouse_cord{ { 115, 40, 100, 50 } },
	scrollBar_folders{ { 1089, 141, 80, 750 }, SDL_Color{ 60, 60, 60, 255 }, 80 },
	objectType_optionsBar{ {745, 90, 313, 38 }, SDL_Color{ 50, 100, 170, 255 }, 55 },
	map_optionsBar{ { 115, 90, 500, 38 }, SDL_Color{ 0, 156, 125, 255 }, 55 },
	objects_typePanel{ { 8, 365, 99, 500 },  SDL_Color{ 125, 125 , 125, 255 }, 100, 20, 5 },
	menu_options{ { 5, 141, 105, 40 }, "data/local_menus/Options/Options.png", true, false, 40 },
	Level_name{ 130, 15, "data/fonts/standard_font.ttf", 30, { 255, 255, 255, 255 } },
	Map_name{ 400, 15, "data/fonts/standard_font.ttf", 30, { 255, 255, 255, 255 } },
	plus{ { 1080, 30, 40, 30 }, "data/engine_files/plus.png", &Base_OBJ::update_multiplierUP },
	minus{ { 1080, 80, 40, 30 }, "data/engine_files/minus.png", &Base_OBJ::update_multiplierDOWN }
{
	scrollBar_folders = {
		new Folder_button{ "Enemies", "data/textures/test.png", &Buttons_OBJ_create::Enemy::create_TEST }, // posiada dwie warstwy otexturowania. Jedna to kolor -> renderowana jako pierwsza, druga to textura w³¹œciwa
		new Folder_button{ "Enemies", "data/textures/test2.png", &Buttons_OBJ_create::Enemy::create_TEST2 },
		new Folder_button{ "Enemies", "data/textures/test3.png", &Buttons_OBJ_create::Enemy::create_TEST3 },
		new Folder_button{ "Enemies", "data/textures/test4.png", &Buttons_OBJ_create::Enemy::create_TEST4 },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" },
		new Folder_button{ "Enemies", "data/engine_files/test.png" }
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

	using namespace MenuLocal_functions;

	menu_options = {
		new Button{ "data/local_menus/Options/SAVE.png", &Menu_options::button_Save },
		new Button_input{ "data/local_menus/Options/SAVE_AS.png", "SAVE LEVEL AS:", &Menu_options::button_SaveAs },
		new Button_input{ "data/local_menus/Options/LOAD.png", "LOAD LEVEL:", &Menu_options::button_Load },
		new Button{ "data/local_menus/Options/EXIT.png", &Menu_options::button_Exit }
	};

	objectType_optionsBar = {
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" }
	};

	objects_typePanel = {
		new Button{ "data/menus scrollbar/dynamic_objectsPlacer module.png" },
		new Button{ "data/menus scrollbar/block_placer module.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" },
		new Button{ "data/engine_files/test.png" }
	};
}

void LevelCreator::events_multiwindow()
{
	menu_options.events();
}

// zdarzenia zale¿ne od myszki lub klawiatury
void LevelCreator::events()
{
	map_edit_area.events();
	objectType_optionsBar.events();
	menu_options.events();
	objects_typePanel.events();

	plus.events();
	minus.events();

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
	//objectType_optionsBar.render();
	objects_typePanel.render();

	map_edit_area.render();

	menu_options.render();

	plus.render();
	minus.render();

	Level_name.render();
	Map_name.render();

	if (map_edit_area.is_mouseOver())
		map_coordinate.render();
	mouse_cord.render();
}

void LevelCreator::save_level()
{
	map_edit_area.save_Objects(LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName());

	using std::ios_base;

	level_save.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".properties").c_str(), ios_base::out | ios_base::binary);
	level_save.write(LevelEditor_manager::get_backgroundName().c_str(), LevelEditor_manager::get_backgroundName().size());
	level_save.close();

	level_save.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".config").c_str(), ios_base::out | ios_base::binary);
	level_save.write(reinterpret_cast<const char *>(&Base_OBJ::get_multiplier()), sizeof(Base_OBJ::get_multiplier()));
	level_save.close();
}

void LevelCreator::load_Level()
{
	using std::ios_base;

	char nazwa[100]{};

	level_load.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".properties").c_str(), ios_base::in | ios_base::binary);
	level_load.read(nazwa, 100);
	level_load.close();
	LevelEditor_manager::set_backgroundName(nazwa);

	double multiplier;
	level_load.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".config").c_str(), ios_base::in | ios_base::binary);
	level_load.read(reinterpret_cast<char*>(&multiplier), sizeof(double));
	level_load.close();
	Base_OBJ::set_size_multiplier(multiplier);

	map_edit_area.load_Objects(LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName());
	map_coordinate.set(&map_edit_area.get_position(), &map_edit_area.get_backgroundArea()); // zamiana stanu na other
}

void LevelCreator::new_Level()
{
	Base_OBJ::reset_multiplier();
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
		break;
	}
}

void LevelCreator::switch_Management_state()
{
	if (LevelEditor_manager::get_Management_state() != LevelEditor_Management_state::NONE) {
		switch (LevelEditor_manager::get_Management_state())
		{
		case LevelEditor_Management_state::CREATE_NEW_LEVEL:
			new_Level();
			LevelEditor_manager::reset();
			map_edit_area.reset();

			Level_name.update("LEVEL:   " + LevelEditor_manager::get_levelName());
			Map_name.update("MAP:   " + LevelEditor_manager::get_backgroundName());
			break;
		case LevelEditor_Management_state::LOAD_LEVEL:
			load_Level();
			LevelEditor_manager::reset();

			Level_name.update("LEVEL:   " + LevelEditor_manager::get_levelName());
			Map_name.update("MAP:   " + LevelEditor_manager::get_backgroundName());
			break;
		case LevelEditor_Management_state::SAVE_CURRENT_LEVEL: // zapisz pod nazw¹ wprowadzon¹ poczas wpisywania nazwy na samym pocz¹tku
			save_level(); // zapisz pod nazw¹ któr¹ podawano przy ³adowaniu/tworzeniu levela
			LevelEditor_manager::set_Management_state(LevelEditor_Management_state::NONE); // przywróæ poprzedni stan
			break;
		case LevelEditor_Management_state::SAVE_AS: // Zapisz pod inn¹ nazw¹
			save_level();
			Level_name.update("LEVEL:   " + LevelEditor_manager::get_levelName());
			Map_name.update("MAP:   " + LevelEditor_manager::get_backgroundName());
			LevelEditor_manager::set_Management_state(LevelEditor_Management_state::NONE);
			break;
		}
	}
}