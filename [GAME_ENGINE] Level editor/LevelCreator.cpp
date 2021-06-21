#include "LevelCreator.h"
#include "LevelEditor_manager.h"
#include "Menu_manager.h"
#include "Map_manager.h"
#include "Folder_button.h"
#include "Buttons_OBJ_create.h"
#include "Buttons_Map_Functions.h"
#include "CoordinateBar_map.h"
#include "Event_handlerOBJ_map.h"
#include "Event_handler.h"
#include "Engine_manager.h"

LevelCreator::LevelCreator() : // inicjuje wszystkie dane Level Creatora - ustala funkcje przycisków itd.
	map_edit_area{ { 160, 128, 1200, 600 } },
	mouse_cord{ { 115, 40, 100, 50 } },
	scrollBar_folders{ { 1089, 141, 80, 750 }, SDL_Color{ 60, 60, 60, 255 }, 80 },
	objectType_optionsBar{ { 745, 90, 313, 38 }, SDL_Color{ 50, 100, 170, 255 }, 55 },
	map_optionsBar{ { 115, 90, 500, 38 }, SDL_Color{ 0, 156, 125, 255 }, 55 },
	Level_name{ 130, 15, "data/fonts/standard_font.ttf", 30, { 255, 255, 255, 255 } },
	Map_name{ 400, 15, "data/fonts/standard_font.ttf", 30, { 255, 255, 255, 255 } },
	plus{ { 1080, 30, 40, 30 }, "data/engine_files/plus.png", &Base_OBJ::update_multiplierUP },
	minus{ { 1080, 80, 40, 30 }, "data/engine_files/minus.png", &Base_OBJ::update_multiplierDOWN }
{
	CoordinateBar_map::Init({ 300, 40, 100, 50 }, &map_edit_area.get_position(), &map_edit_area.get_backgroundArea());

	scrollBar_folders = {
		BButton_ptr{ new Folder_button{ "data/textures/test.png", &Buttons_OBJ_create::Enemy::create_TEST } }, // posiada dwie warstwy otexturowania. Jedna to kolor -> renderowana jako pierwsza, druga to textura w³¹œciwa
		BButton_ptr{ new Folder_button{ "data/textures/test2.png", &Buttons_OBJ_create::Enemy::create_TEST2 } },
		BButton_ptr{ new Folder_button{ "data/textures/test3.png", &Buttons_OBJ_create::Enemy::create_TEST3 } },
		BButton_ptr{ new Folder_button{ "data/textures/test4.png", &Buttons_OBJ_create::Enemy::create_TEST4 } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } }
	};

	map_optionsBar = {
		BButton_ptr{ new Folder_button{ "data/engine_files/single_object_selecting.png", &Buttons_Map_Functions::onClick::single_select_button } },
		BButton_ptr{ new Folder_button{ "data/engine_files/multi_object_selecting.png", &Buttons_Map_Functions::onClick::multi_select_button } },
		BButton_ptr{ new Folder_button{ "data/engine_files/delete.png",  &Buttons_Map_Functions::onClick::delete_button } },
		BButton_ptr{ new Folder_button{ "data/engine_files/map_move.png", &Buttons_Map_Functions::onClick::moveMap_button } },
		// teraz dla testow
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Folder_button{ "data/engine_files/test.png" } }
		// koniec testow
	};

	objectType_optionsBar = {
		BButton_ptr{ new Button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Button{ "data/engine_files/test.png" } },
		BButton_ptr{ new Button{ "data/engine_files/test.png" } }
	};

	map_edit_area.set_cord(&mouse_cord);
}

void LevelCreator::events_multiwindow()
{
	bar_modules_left.events_multiwindow();
}

void LevelCreator::reset_states()
{
	map_optionsBar.reset(); // zresetuj dane stany i usun wyró¿nienia przycisków
	scrollBar_folders.reset();
	bar_modules_left.reset_states();
}

// zdarzenia zale¿ne od myszki lub klawiatury
void LevelCreator::events()
{
	if (Keyboard::is_pressed_LCNTRL_Z())
	{
		Engine_manager::setState(Engine_state::IS_IN_MENU);
	}

	map_edit_area.events();
	//objectType_optionsBar.events();

	bar_modules_left.events();

	plus.events();
	minus.events();

	scrollBar_folders.events();

	map_optionsBar.events();

	// tymczasowe brzydkie rozwi¹zanie -> do zmiany w przysz³oœci

	if (scrollBar_folders.is_buttonClicked()) {
		//objectType_optionsBar.deactivate_buttons();
		map_optionsBar.deactivate_buttons();
	}
	else if (objectType_optionsBar.is_buttonClicked()) {
		scrollBar_folders.deactivate_buttons();
		map_optionsBar.deactivate_buttons();
	}
	else if (map_optionsBar.is_buttonClicked()) {
		scrollBar_folders.deactivate_buttons();
		//objectType_optionsBar.deactivate_buttons();
	}
}

void LevelCreator::events_indp()
{

	/*if (Keyboard::is_pressedOnce({Key::LCNTRL, Key::Z}))
		Engine_manager::setState(Engine_state::IS_IN_MENU);*/

	CoordinateBar_map::events(map_edit_area.is_mouseOver());

	bar_modules_left.events_indp();

	mouse_cord.events();

	//switch_Main_state();
	map_edit_area.events_indp();
	switch_Management_state();
}

void LevelCreator::render()
{
	scrollBar_folders.render();
	map_optionsBar.render();

	map_edit_area.render();

	bar_modules_left.render();

	minus.render();
	plus.render();

	Level_name.render();
	Map_name.render();

	CoordinateBar_map::render(map_edit_area.is_mouseOver());

	mouse_cord.render();
}

void LevelCreator::save_level()
{
	std::ofstream level_save; // zapisuje dane ca³ego levela

	map_edit_area.save_Objects(LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName());

	using std::ios_base;

	level_save.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".properties").c_str(), ios_base::out | ios_base::binary);
	level_save.write(LevelEditor_manager::get_backgroundName().c_str(), LevelEditor_manager::get_backgroundName().size());
	level_save.close();

	level_save.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".config").c_str(), ios_base::out | ios_base::binary);
	level_save.write(reinterpret_cast<const char *>(&Base_OBJ::get_multiplier()), sizeof(Base_OBJ::get_multiplier()));
	level_save.close();
}

void LevelCreator::reset_mapStates()
{
	map_edit_area.reset();
}

void LevelCreator::load_Level()
{
	std::ifstream level_load; // ³aduje dane ca³ego levela
	reset_states();
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
}

void LevelCreator::new_Level()
{
	reset_states();
	Base_OBJ::reset_multiplier();
	map_edit_area.reset();
	map_edit_area.set_background(LevelEditor_manager::get_levels_mapsPath() + LevelEditor_manager::get_backgroundName() + ".png");
}

void LevelCreator::keyboardHandler()
{

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