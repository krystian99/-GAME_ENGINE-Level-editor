#include "Button.h"
#include "Mouse.h"
//TEST
#include <iostream>
using std::cout;
using std::endl;
//END TEST
Button::Button(std::string(*point)(int x, int y), std::string pathTX)
{
	loadTX(pathTX);
	pointer = point;
}

void Button::generateCode() const
{

}

void Button::onClick()
{
	// TEST
	cout << "Button clicked!" << endl;
	// END TEST
}

void Button::setPosition(const SDL_Rect & rt)
{
	position = { rt.x, rt.y, rt.w, rt.h };
}

void Button::render(SDL_Renderer * rn, SDL_RendererFlip flip)
{
	tX.render(rn, &position, flip);
	SDL_RenderDrawRect(rn, &position);
}

void Button::mouse_handler()
{
	if (Mouse::getMousePOSx() >= position.x && Mouse::getMousePOSx() <= position.x + position.w
		&& Mouse::getMousePOSy() >= position.y && Mouse::getMousePOSy() <= position.y + position.h) 
	{
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

