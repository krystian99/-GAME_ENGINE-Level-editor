#include "Button.h"
#include "Mouse.h"
//TEST
#include <iostream>
using std::cout;
using std::endl;
//END TEST

Button::~Button() {}

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

void Button::render(SDL_Renderer * rn, SDL_Rect * rt, SDL_RendererFlip flip)
{
	if (rt) { // renderuj czêœæ textury
		double scaleX = double(tX.getWidth()) / double(Width); // skalowanie rozmiaru
		double scaleY = double(tX.getHeight()) / double(Height); // skalowanie rozmiaru

		int y = tX.getHeight() - (rt->h * scaleY);
		int h = tX.getHeight() - y;

		int x = tX.getWidth() - (rt->w * scaleX);
		int w = tX.getWidth() - x;

		SDL_Rect clip = { x, y, w, h };
		tX.render(rn, &clip, rt, flip);
		SDL_RenderDrawRect(rn, rt);
	}
	else { // renderuj ca³¹ texturê
		tX.render(rn, nullptr, &position, flip);
		SDL_RenderDrawRect(rn, &position);
	}
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

