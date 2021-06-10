#include "Menu_Animation.h"
#include "Engine_manager.h"
#include "Animation_manager.h"
#include "Error.h"

Menu_Animation::Menu_Animation() :
	input_animName{ { 100, 30, 200, 70 }, 130, 40, "data/fonts/standard_font.ttf", 50,{ 0, 0, 255 } },
	input_amountOf_frames{ { 300, 30, 200, 70 }, 330, 40, "data/fonts/standard_font.ttf", 50,{ 0, 0, 255 }, true, false },
	newConfig{ { 100, 100, 300, 100 }, 130, 115, "data/fonts/standard_font.ttf", "New animConfig", 50,{ 0, 255, 190 } },
	loadConfig{ { 100, 200, 300, 100 }, 130, 215, "data/fonts/standard_font.ttf", "Load animConfig", 50,{ 0, 255, 190 } }
{}

void Menu_Animation::events() // nie ma takiej potrzeby ¿eby tworzyæ specjalnych obiekty, skoro i tak s¹ tylko raz tworzone w tym miejscu i potrzebuj¹ wsparcia g³ównej klasy menu ¿eby wykonaæ dana czynnoœæ
{
	input_animName.events();
	input_amountOf_frames.events();

	if (input_animName.is_clicked()) {
		input_animName.setCurrent(true);
		input_amountOf_frames.setCurrent(false);
	}
	else if (input_amountOf_frames.is_clicked()) {
		input_animName.setCurrent(false);
		input_amountOf_frames.setCurrent(true);
	}
}

void Menu_Animation::events_indp()
{
	newConfig.events();
	loadConfig.events();

	if (newConfig.is_clicked() && !input_animName.is_empty() && !input_amountOf_frames.is_empty()) {
		if (Animation_manager::create_newConfig(input_animName.getStr(), input_amountOf_frames.getStr()))
			Engine_manager::setState(Engine_state::IS_IN_ANIMATION_MANAGEMENT);
	}
	else if (loadConfig.is_clicked() && !input_animName.is_empty()) {
		if (Animation_manager::load_Config(input_animName.getStr()))
			Engine_manager::setState(Engine_state::IS_IN_ANIMATION_MANAGEMENT);
	}
}

void Menu_Animation::render()
{
	newConfig.render();
	loadConfig.render();

	input_animName.render();
	input_amountOf_frames.render();
}