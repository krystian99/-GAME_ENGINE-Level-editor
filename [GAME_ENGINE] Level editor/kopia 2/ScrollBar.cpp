#include "ScrollBar.h"
#include "Mouse.h"
#include "Setup.h"
#include "Buttons_resources.h"

/*// TEST
#include <iostream>
using std::cout;
using std::endl;
// END TEST*/
ScrollBar::ScrollBar(ButtonType type, SB_Orientation orient) :
	orientation{ orient }, button_type{ type }
{}

void ScrollBar::load_images()
{
	tX.loadFromFile("files/ScrollBarsTX/background.png"); // ³aduje t³o scrollbara

	switch (button_type) {
	case ButtonType::STATIC:
		for (int i = 0; i < buttons.size(); i++)
			buttons[i].loadTX(Buttons_TX::Static_textures[i]);
		break;
	case ButtonType::DYNAMIC:
		for (int i = 0; i < buttons.size(); i++)
			buttons[i].loadTX(Buttons_TX::Dynamic_textures[i]);
		break;
	case ButtonType::KEY:
		for (int i = 0; i < buttons.size(); i++)
			buttons[i].loadTX(Buttons_TX::Key_textures[i]);
		break;
	}
}

void ScrollBar::SetPOSition(SDL_Rect rt)
{
	Init(rt);
}

void ScrollBar::render(SDL_Renderer * rn)
{
	tX.render(rn, &barPOS);
	for (auto & bt : buttons)
		bt.render(rn);
}

void ScrollBar::mouse_handler()
{
	if (Mouse::getMousePOSx() >= barPOS.x && Mouse::getMousePOSx() <= barPOS.x + barPOS.w
		&& Mouse::getMousePOSy() >= barPOS.y && Mouse::getMousePOSy() <= barPOS.y + barPOS.h)
	{
		if (Mouse::getWheelUpState()) {
			mouse_wheelDir = Mouse_Wheel_Dir::UP;
			setButtonsPOS(MOVE_SIZE);
		}
		else if (Mouse::getWheelDownState()) {
			mouse_wheelDir = Mouse_Wheel_Dir::DOWN;
			setButtonsPOS(-MOVE_SIZE);
		}
	}
}

void ScrollBar::events(SDL_Event * ev)
{
	mouse_handler();
	for (auto & button : buttons)
		button.mouse_handler();
}

void ScrollBar::Init(const SDL_Rect & rt) // inicjuje wszystkie sk³adniki, ustawia pozycje przycisków i scrollbara
{
	barPOS = { rt.x, rt.y, rt.w, rt.h };

	switch (button_type) {
	case ButtonType::DYNAMIC:
		buttons.resize(Buttons_TX::Dynamic_textures.size());
		break;
	case ButtonType::KEY:
		buttons.resize(Buttons_TX::Key_textures.size());
		break;
	case ButtonType::STATIC:
		buttons.resize(Buttons_TX::Static_textures.size());
		break;
	}
	load_images();
	setStartButtonPOS();
}

void ScrollBar::setButtonsPOS_horizontal(int size) // przesuwa przyciski o okreœlony rozmiar
{
	if (mouse_wheelDir == Mouse_Wheel_Dir::DOWN){
		if (buttons_pos.currentStartX + size > barPOS.x)
			setHorizontal(size);
		else if (buttons_pos.currentStartX > barPOS.x + FRAME_SIZE)
			setHorizontal(-FRAME_SIZE);
		else return;
	}
	else if (mouse_wheelDir == Mouse_Wheel_Dir::UP) {
		if (buttons_pos.currentEndX + size < barPOS.x + barPOS.w)
			setHorizontal(size);
		else if (buttons_pos.currentEndX < barPOS.x + barPOS.w - FRAME_SIZE)
			setHorizontal(barPOS.x + barPOS.w - buttons_pos.currentEndX);
		else return;
	}
}

void ScrollBar::setButtonsPOS_vertical(int size) // przesuwa przyciski o okreœlony rozmiar 
{
	if (mouse_wheelDir == Mouse_Wheel_Dir::UP && buttons_pos.currentStartY < barPOS.y + FRAME_SIZE) {
		if (buttons_pos.currentStartY + size < barPOS.y)
			setVertical(size);
		else if (buttons_pos.currentStartY < barPOS.y)
			setVertical(FRAME_SIZE);
		else return;
	}
	else if (mouse_wheelDir == Mouse_Wheel_Dir::DOWN && buttons_pos.currentEndY > barPOS.y + barPOS.h - FRAME_SIZE) {
		if (buttons_pos.currentEndY + size > barPOS.y + barPOS.h)
			setVertical(size);
		else if (buttons_pos.currentEndY > barPOS.y + barPOS.h)
			setVertical(barPOS.y + barPOS.h - buttons_pos.currentEndY);
		else return;
	}
}

void ScrollBar::setButtonsPOS(const int & size)
{
	switch_orientation(size);
}

void ScrollBar::setWidthHeight(const int & width, const int & height)
{
	if (orientation == SB_Orientation::VERTICAL)
		buttons_pos = { barPOS.x + 5, barPOS.y, width, height };
	else
		buttons_pos = { barPOS.x, barPOS.y + 5, width, height };
}

void ScrollBar::switch_orientation(const int & size)
{
	switch (orientation) {
	case SB_Orientation::VERTICAL:
		setButtonsPOS_vertical(size);
		break;
	case SB_Orientation::HORIZONTAL:
		setButtonsPOS_horizontal(size);
		break;
	}
}

void ScrollBar::setHorizontal(const int & size)
{
	int width = Button::getWidth();
	int height = Button::getHeight();

	int X = buttons_pos.currentStartX;
	int Y = buttons_pos.currentStartY;

	for (auto & bt : buttons) {
		bt.setPosition({ X + size, Y, width, height });
		X += width;
	}
	buttons_pos.currentStartX += size;
	buttons_pos.currentEndX += size;
}

void ScrollBar::setVertical(const int & size)
{
	int width = Button::getWidth();
	int height = Button::getHeight();

	int X = buttons_pos.currentStartX;
	int Y = buttons_pos.currentStartY;

	for (auto & bt : buttons) {
		bt.setPosition({ X, Y + size, width, height });
		Y += height;
	}
	buttons_pos.currentStartY += size;
	buttons_pos.currentEndY += size;
}

void ScrollBar::setStartButtonPOS()
{
	if (orientation == SB_Orientation::HORIZONTAL)
	{
		int width = Button::getWidth();
		int height = Button::getHeight();

		int X = barPOS.x + 10;
		int Y = barPOS.y + 5;

		for (auto & bt : buttons) {
			bt.setPosition({ X, Y, width, height });
			X += width;
		}
		setWidthHeight(X, Y);
	}
	else {
		int width = Button::getWidth();
		int height = Button::getHeight();

		int X = barPOS.x + 5;
		int Y = barPOS.y + 5;

		for (auto & bt : buttons) {
			bt.setPosition({ X, Y, width, height });
			Y += height;
		}
		setWidthHeight(X, Y);
	}
}
