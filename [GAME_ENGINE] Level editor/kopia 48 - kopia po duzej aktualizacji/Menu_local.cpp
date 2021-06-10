#include "Menu_local.h"
#include "Video_Info.h"
#include "Mouse.h"

Menu_local::Menu_local(SDL_Rect rt, const std::string & tx_str, bool Active, bool Can_hide, int expand_size_button) :
	active{ Active }, can_hide{ Can_hide }
{
	button_height = std::round(expand_size_button * Video_Info::get_scaleH());
	position.x = std::round(rt.x * Video_Info::get_scaleW());
	position.y = std::round(rt.y * Video_Info::get_scaleH());
	position.w = std::round(rt.w * Video_Info::get_scaleW());
	position.h = std::round(rt.h * Video_Info::get_scaleH());

	tX.loadFromFile(tx_str);
}

void Menu_local::render()
{
	tX.render(nullptr, &position);

	if (active) {
		for (auto & button : buttons)
			button->render();
	}
}

void Menu_local::events()
{
	mouse_handler();

	if (active) {
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

	int x = position.x;
	int y = position.y + position.h;

	for (auto & button : buttons) {
		button->set_position({ x, y, position.w, button_height });
		y += button_height;
	}
}

void Menu_local::mouse_handler()
{
	if (Mouse::getX() >= position.x && Mouse::getX() <= position.x + position.w
		&& Mouse::getY() >= position.y && Mouse::getY() <= position.y + position.h)
	{
		if (Mouse::getBt_state() == Mouse_key::L_BUTTON) {
			if (can_hide)
				active = !active;
		}
	}
}

void Menu_local::script_run()
{

}

void Menu_local::script_leave()
{

}