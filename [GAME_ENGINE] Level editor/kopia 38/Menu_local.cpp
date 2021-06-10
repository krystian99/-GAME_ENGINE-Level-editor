#include "Menu_local.h"
#include "Video_Info.h"

Menu_local::Menu_local(SDL_Rect rt, const std::string & tx_str, bool Active, int expand) :
	active{ Active }
{
	button_height = std::round(expand * Video_Info::get_scaleH());
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
	for (auto & button : buttons)
		button->events();
}

void Menu_local::operator=(const std::vector<Button*> & Buttons)
{
	buttons = Buttons;

	int x = position.x;
	int y = position.y + position.h;

	for (auto & button : buttons) {
		button->set_position({ x, y, position.w, button_height });
		y += button_height;
	}
}