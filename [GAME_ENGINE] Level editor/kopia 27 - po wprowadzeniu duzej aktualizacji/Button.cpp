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

void Button::render()
{
	tX.render(nullptr, &position);
}

void Button::onClick()
{
	bt_state = Button_State::SELECTED;
	clicked = true;
}

void Button::mouse_handler()
{
	clicked = false;
	if (Mouse::getMousePOSx() >= position.x && Mouse::getMousePOSx() <= position.x + position.w
		&& Mouse::getMousePOSy() >= position.y && Mouse::getMousePOSy() <= position.y + position.h) 
	{
		onMouseOver(); // gdy myszka jest na pozycji przycisku
		if (Mouse::getButtonState() == Mouse_key::L_BUTTON) {
			//clicked = true;
			//bt_state = Button_State::SELECTED;
			l_bt_pressing = true;
			//onClick();
		}
		else if (Mouse::getButtonState() == Mouse_key::NONE && l_bt_pressing) {
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

