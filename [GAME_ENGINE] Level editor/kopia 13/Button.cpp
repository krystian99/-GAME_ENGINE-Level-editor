#include "Button.h"
#include "Mouse.h"

void Button::Init(const SDL_Rect & rt)
{
	position = { rt.x, rt.y, rt.w, rt.h };
	Width = rt.w;
	Height = rt.h;
}

void Button::setPosition(const SDL_Rect & rt)
{
	position = rt;
}

void Button::render(SDL_Renderer * rn)
{
	tX.render(rn, nullptr, &position);
}

void Button::mouse_handler()
{
	clicked = false;
	if (Mouse::getMousePOSx() >= position.x && Mouse::getMousePOSx() <= position.x + position.w
		&& Mouse::getMousePOSy() >= position.y && Mouse::getMousePOSy() <= position.y + position.h) 
	{
		onMouseOver(); // gdy myszka jest na pozycji przycisku
		if (Mouse::get_lButton_State())
			l_bt_pressing = true;
		else if (!Mouse::get_lButton_State() && l_bt_pressing) {
			bt_state = Button_State::SELECTED;
			clicked = true;
			onClick();
			l_bt_pressing = false;
		}
	}
}

void Button::setState(const Button_State & stateToChange)
{
	bt_state = stateToChange;
}

void Button::loadTX(std::string path)
{
	tX.loadFromFile(path);
}

