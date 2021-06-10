#include "Menu_start.h"
#include "Engine_manager.h"
#include "LevelEditor_manager.h"
#include "Error.h"

Menu_start::Menu_start()
{
	input_levelname = std::unique_ptr<InputArea>{ new InputArea{ { 100, 30, 200, 70}, 130, 40, "data/fonts/standard_font.ttf", 50, { 0, 0, 255 } } };
	input_background = std::unique_ptr<InputArea>{ new InputArea{ { 300, 30, 200, 70 }, 330, 40, "data/fonts/standard_font.ttf", 50,{ 0, 0, 255 } } };
	
	New = std::unique_ptr<Button_Menu>{ new Button_Menu{ { 100, 100, 200, 100 }, 130, 115, "data/fonts/standard_font.ttf", "NEW LEVEL", 50,{ 0, 255, 190 } } };
	Load = std::unique_ptr<Button_Menu>{ new Button_Menu{ { 100, 200, 200, 100 }, 130, 215, "data/fonts/standard_font.ttf", "LOAD LEVEL", 50, { 0, 255, 190 } } };

	if (!New || !Load || !input_background || !input_levelname)
		throw Error::throw_Message("Cannot allocate memory at Menu Start!");
}

void Menu_start::events() // nie ma takiej potrzeby ¿eby tworzyæ specjalnych obiekty, skoro i tak s¹ tylko raz tworzone w tym miejscu i potrzebuj¹ wsparcia g³ównej klasy menu ¿eby wykonaæ dana czynnoœæ
{
	input_levelname->events();
	input_background->events();

	if (input_levelname->is_clicked()) {
		input_levelname->setCurrent(true);
		input_background->setCurrent(false);
	}
	else if (input_background->is_clicked()) {
		input_levelname->setCurrent(false);
		input_background->setCurrent(true);
	}
}

void Menu_start::events_indp()
{
	New->events();
	Load->events();

	if (New->is_clicked() && !input_levelname->is_empty() && !input_background->is_empty()) {
		if (LevelEditor_manager::create_newLevel(input_levelname->getStr(), input_background->getStr()))
			Engine_manager::setState(Engine_state::IS_IN_LC);
	}
	else if (Load->is_clicked() && !input_levelname->is_empty()) {
		if (LevelEditor_manager::loadLevel(input_levelname->getStr()))
			Engine_manager::setState(Engine_state::IS_IN_LC);
	}
}

void Menu_start::render()
{
	New->render();
	Load->render();

	input_levelname->render();
	input_background->render();
}