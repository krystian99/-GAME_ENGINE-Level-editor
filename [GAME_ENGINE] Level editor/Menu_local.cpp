#include "Menu_local.h"
#include "Video_Info.h"
#include "Mouse.h"

Menu_local::Menu_local(SDL_Rect rt, const std::string & tx_str, bool Active, bool Can_hide, int expand_size_button) :
	Button{ rt, tx_str }, can_hide{ Can_hide }, script_test{ 10 }
{
	set_active(Active);

	button_height = std::round(expand_size_button * Video_Info::get_scaleH());

	tX.loadFromFile(tx_str);
}

void Menu_local::render()
{
	Button::render();

	if (!script_test.is_finished())
		script_test.render_buttons(buttons, getPOS().y + getPOS().h);

	else if (is_active())
	{
		for (auto & button : buttons)
			button->render();
	}
}

void Menu_local::events()
{
	Button::events();

	if (script_test.is_finished() && is_active())
	{
		for (auto & button : buttons) {
			button->events();
			if (button->is_mouseKey_1hit(Mouse_key::L_BUTTON)) {
				current_button = button.get();
				break;
			}
		}
	}
}

void Menu_local::events_indp()
{
	if (!script_test.is_finished())
		script_test.events_buttons(buttons);
}

void Menu_local::operator=(const std::vector<BButton_ptr> & Buttons)
{
	buttons = std::move(Buttons);

	auto pos = getPOS();

	int x = pos.x;
	int y = pos.y + pos.h;

	for (auto & button : buttons) {
		button->set_position({ x, y, pos.w, button_height });
		y += button_height;
	}

	auto back_pos = buttons.back()->getPOS();
	auto start_posY = back_pos.y + back_pos.h;

	script_test.set_endPOS(back_pos.y);
	script_test.set_startPOS(getPOS().y); // jak na razie punkt startowy dla testow
}

void Menu_local::on_mouseL1hit()
{
	//Button::on_mouseL1hit();

	if (!is_active())
		set_active(true);
	else
		set_active(false);
}

void Menu_local::on_Deactivate() // uruchom skrypt wy³¹czania
{
	if (can_hide)
		script_test.leave();
}

void Menu_local::on_Activate() // uruchom skrypt w³¹czania
{
	if (can_hide)
		script_test.run();
}

void Script::run()
{
	script_state = Script_state::SCRIPT_ENTERING;
	finished = false;
}

void Script::leave()
{
	script_state = Script_state::SCRIPT_LEAVING;
	finished = false;
}

void Script::entering_events(std::vector<BButton_ptr> & buttons)
// skrypt jest w trakcie otworzenia i jest wywo³ywany do momentu ustlonego warunku -> wartosæ finished zostaje wtedy zmieniona na true
{
	if (buttons.back()->getPOS().y < end_posY) {
		if (buttons.back()->getPOS().y + move_speed < end_posY)
			move_buttons(buttons, move_speed);
		else
		{
			int temp_speed = end_posY - buttons.back()->getPOS().y;
			move_buttons(buttons, temp_speed);
		}
	}
	else
		finished = true;
}

void Script::leaving_events(std::vector<BButton_ptr> & buttons)
//  skrypt jest w trakcie wy³¹czania i jest wywo³ywany do danego warunku -> --||--
{
	if (buttons.back()->getPOS().y > start_posY) {
		if (buttons.back()->getPOS().y - move_speed > start_posY)
			move_buttons(buttons, -move_speed);
		else
		{
			int temp_speed = std::abs(start_posY - buttons.back()->getPOS().y);
			move_buttons(buttons, -temp_speed);
		}
	}
	else
		finished = true;
}

void Script::events_buttons(std::vector<BButton_ptr> & buttons)
{
	switch (script_state) {
	case Script_state::SCRIPT_ENTERING:
		entering_events(buttons);
		break;
	case Script_state::SCRIPT_LEAVING:
		leaving_events(buttons);
		break;
	}
}

void Script::render_buttons(std::vector<BButton_ptr> & buttons, const int & render_fromY) // cos podobnego do skryptu domyslnei wgranego w ScrollBar'u
{
	static SDL_Rect temp_pos, texture_area;

	for (auto & button : buttons) {
		auto & pos = button->getPOS();

		if (pos.y >= render_fromY)
			button->render();
		else if (pos.y < render_fromY && pos.y + pos.h > render_fromY) {
			temp_pos = { pos.x, render_fromY, pos.w, pos.y + pos.h - render_fromY };

			auto & tX = button->getTX();

			double scale = double(temp_pos.h) / double(pos.h);

			texture_area.x = 0;
			texture_area.y = tX.getHeight() - std::round(tX.getHeight() * scale);
			texture_area.w = tX.getWidth();
			texture_area.h = tX.getHeight() - texture_area.y;

			button->render(texture_area, temp_pos);
		}
	}
}

void Script::set_startPOS(int start)
{
	start_posY = start;
}

void Script::set_endPOS(int end)
{
	end_posY = end;
}

void Script::move_buttons(std::vector<BButton_ptr>& buttons, int size)
{
	for (auto & button : buttons)
		button->update_about(0, size);
}