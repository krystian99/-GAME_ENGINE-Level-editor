#include "Bar_modules_left.h"
#include "Button_input.h"
#include "MenuLocal_func.h"

Bar_modules_left::Bar_modules_left() :
	menu_options{ { 5, 141, 105, 40 }, "data/local_menus/Options/Options.png", true, true, 40 },
	modules_list{ { 8, 365, 99, 500 },  SDL_Color{ 125, 125 , 125, 255 }, 100, 20, 5 }
{
	using namespace MenuLocal_functions;

	menu_options = {
		new Button{ "data/local_menus/Options/SAVE.png", &Menu_options::button_Save },
		new Button_input{ "data/local_menus/Options/SAVE_AS.png", "SAVE LEVEL AS:", &Menu_options::button_SaveAs },
		new Button_input{ "data/local_menus/Options/LOAD.png", "LOAD LEVEL:", &Menu_options::button_Load },
		new Button{ "data/local_menus/Options/EXIT.png", &Menu_options::button_Exit }
	};

	modules_list = {
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

void Bar_modules_left::events()
{
	if (!moving_objects) {
		menu_options.events();
		modules_list.events();
	}
}

void Bar_modules_left::events_multiwindow()
{
	menu_options.events();
}

void Bar_modules_left::events_indp()
{
	menu_options.events_indp();
	if (!menu_options.get_scriptInfo().is_finished()) {
		moving_objects = true;
		auto & script_info = menu_options.get_scriptInfo();
		modules_list.update_about(script_info.get_moveSpeedX(), script_info.get_moveSpeedY());
	}
	else {
		moving_objects = false;
	}
}

void Bar_modules_left::render()
{
	menu_options.render();
	modules_list.render();
}