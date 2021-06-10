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
	//position = { rt.x, rt.y, rt.w, rt.h };
}

void Button::render(SDL_Renderer * rn)
{
	tX.render(rn, nullptr, &position);
}

void Button::mouse_handler()
{
	if (Mouse::getMousePOSx() >= position.x && Mouse::getMousePOSx() <= position.x + position.w
		&& Mouse::getMousePOSy() >= position.y && Mouse::getMousePOSy() <= position.y + position.h) 
	{
		onMouseOver(); // gdy myszka jest na pozycji przycisku
		if (Mouse::get_lButton_State() && !clicked) {
			clicked = true;
			onClick();
		}
		else if (!Mouse::get_lButton_State())
			clicked = false;
	}
}

void Button::loadTX(std::string path)
{
	tX.loadFromFile(path);
}

