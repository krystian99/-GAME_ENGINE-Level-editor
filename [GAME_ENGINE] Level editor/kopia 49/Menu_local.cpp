#include "Menu_local.h"
#include "Video_Info.h"
#include "Mouse.h"

Menu_local::Menu_local(SDL_Rect rt, const std::string & tx_str, bool Active, bool Can_hide, int expand_size_button) :
	Button{ rt, tx_str }, can_hide{ Can_hide }
{
	set_active(Active);

	button_height = std::round(expand_size_button * Video_Info::get_scaleH());

	tX.loadFromFile(tx_str);
}

void Menu_local::render()
{
	Button::render();

	if (is_active()) {
		for (auto & button : buttons)
			button->render();
	}
}

void Menu_local::events()
{
	Button::events();

	if (is_active()) {
		for (auto & button : buttons) {
			button->events();
			if (button->is_mouseKey_1hit(Mouse_key::L_BUTTON)) {
				current_button = button;
				break;
			}
		}
	}
}

void Menu_local::operator=(const std::vector<Button*> & Buttons)
{
	buttons = std::move(Buttons);

	auto pos = getPOS();

	int x = pos.x;
	int y = pos.y + pos.h;

	for (auto & button : buttons) {
		button->set_position({ x, y, pos.w, button_height });
		y += button_height;
	}
}

void Menu_local::on_mouseL1hit()
{
	Button::on_mouseL1hit();
}

void Menu_local::on_Deactivate() // uruchom skrypt wy³¹czania
{
	if (can_hide)
		script_leave();
}

void Menu_local::on_Activate() // uruchom skrypt w³¹czania
{
	if (can_hide)
		script_run();
}

void Menu_local::script_run() // przesuñ resztê przycisków na dó³ i w³¹cz timer
{

}

void Menu_local::script_leave()
{

}