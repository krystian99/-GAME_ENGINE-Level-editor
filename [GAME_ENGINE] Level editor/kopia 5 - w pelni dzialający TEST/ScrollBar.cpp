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

void ScrollBar::render(SDL_Renderer * rn)
{
	tX.render(rn, nullptr, &barPOS);
	buttons_render(rn);
}

void ScrollBar::mouse_handler()
{
	if (Mouse::getMousePOSx() >= barPOS.x && Mouse::getMousePOSx() <= barPOS.x + barPOS.w
		&& Mouse::getMousePOSy() >= barPOS.y && Mouse::getMousePOSy() <= barPOS.y + barPOS.h)
	{
		buttons_events();
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
}

void ScrollBar::buttons_events()
{
	for (auto & button : buttons)
		button.mouse_handler();
}

void ScrollBar::buttons_render(SDL_Renderer * rn)
{
	for (auto & bt : buttons)
	{
		switch (orientation)
		{
		case SB_Orientation::HORIZONTAL:
			buttons_render_horizontal(rn, bt);
			break;
		case SB_Orientation::VERTICAL:
			buttons_render_vertical(rn, bt);
			break;
		}
	}
}

void ScrollBar::buttons_render_horizontal(SDL_Renderer * rn, Button & bt)
{
	const SDL_Rect * tmp = bt.getPOS();
	SDL_Rect clip; // obszar textury przycisku

	if (tmp->x >= barPOS.x + FRAME_SIZE && tmp->x + tmp->w <= barPOS.x + barPOS.w - FRAME_SIZE)
		bt.render(rn); // renderowanie ca³ego przycisku

	else if (tmp->x < barPOS.x + FRAME_SIZE && tmp->x + tmp->w > barPOS.x + FRAME_SIZE)
	{
		clip = { barPOS.x + FRAME_SIZE, tmp->y, tmp->x + tmp->w - (barPOS.x + FRAME_SIZE), tmp->h };
		bt.render(rn, &clip); // renderowanie czêœci przycisku
	}

	else if (tmp->x < barPOS.x + barPOS.w - FRAME_SIZE && tmp->x + tmp->w > barPOS.x + barPOS.w - FRAME_SIZE)
	{
		clip = { tmp->x, tmp->y, barPOS.x + barPOS.w - FRAME_SIZE - tmp->x, tmp->h };
		bt.render(rn, &clip); // renderowanie czêœci przycisku
	}
}

void ScrollBar::buttons_render_vertical(SDL_Renderer * rn, Button & bt) // b³¹d - jeden przycisk wgl siê nie renderuje
{
	const SDL_Rect * tmp = bt.getPOS();
	SDL_Rect clip; // obszar textury przycisku

	if (tmp->y >= barPOS.y + FRAME_SIZE && tmp->y + tmp->h <= barPOS.y + barPOS.h - FRAME_SIZE)
		bt.render(rn);

	else if (tmp->y < barPOS.y + FRAME_SIZE && tmp->y + tmp->h > barPOS.y + FRAME_SIZE) {
		clip = { tmp->x, barPOS.y + FRAME_SIZE, tmp->w, tmp->y + tmp->h - (barPOS.y + FRAME_SIZE) };
		bt.render(rn, &clip);
	}

	else if (tmp->y < barPOS.y + barPOS.h - FRAME_SIZE && tmp->y + tmp->h > barPOS.y + barPOS.h - FRAME_SIZE) {
		clip = { tmp->x, tmp->y, tmp->w, barPOS.y + barPOS.h - FRAME_SIZE - tmp->y };
		bt.render(rn, &clip);
	}
}

void ScrollBar::Init(const SDL_Rect & position) // inicjuje wszystkie sk³adniki, ustawia pozycje przycisków i scrollbara
{
	barPOS = { position.x, position.y, position.w, position.h };

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
	if (mouse_wheelDir == Mouse_Wheel_Dir::UP && buttons_pos.currentStartX < barPOS.x + FRAME_SIZE) {
		if (buttons_pos.currentStartX + size <= barPOS.x + FRAME_SIZE)
			moveHorizontal(size);
		else moveHorizontal(barPOS.x + FRAME_SIZE - buttons_pos.currentStartX);
	}
	else if (mouse_wheelDir == Mouse_Wheel_Dir::DOWN && buttons_pos.currentEndX > barPOS.x + barPOS.w - FRAME_SIZE) {
		if (buttons_pos.currentEndX + size >= barPOS.x + barPOS.w - FRAME_SIZE)
			moveHorizontal(size);
		else moveHorizontal(barPOS.x + barPOS.w - FRAME_SIZE - buttons_pos.currentEndX);
	}
}

void ScrollBar::setButtonsPOS_vertical(int size) // przesuwa przyciski o okreœlony rozmiar
{
	if (mouse_wheelDir == Mouse_Wheel_Dir::UP && buttons_pos.currentStartY < barPOS.y + FRAME_SIZE) {
		if (buttons_pos.currentStartY + size <= barPOS.y + FRAME_SIZE)
			moveVertical(size);
		else moveVertical(barPOS.y + FRAME_SIZE - buttons_pos.currentStartY);
	}
	else if (mouse_wheelDir == Mouse_Wheel_Dir::DOWN && buttons_pos.currentEndY > barPOS.y + barPOS.h - FRAME_SIZE) {
		if (buttons_pos.currentEndY + size >= barPOS.y + barPOS.h - FRAME_SIZE)
			moveVertical(size);
		else moveVertical(barPOS.y + barPOS.h - FRAME_SIZE - buttons_pos.currentEndY);
	}
}

void ScrollBar::setButtonsPOS(const int & size)
{
	switch_move_orient(size);
}

void ScrollBar::setWidthHeight(const int & width, const int & height)
{
	if (orientation == SB_Orientation::VERTICAL)
		buttons_pos = { barPOS.x + 5, barPOS.y + FRAME_SIZE, width, height };
	else
		buttons_pos = { barPOS.x + FRAME_SIZE, barPOS.y + 5, width, height };
}

void ScrollBar::switch_move_orient(const int & size)
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

void ScrollBar::moveHorizontal(const int & size)
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

void ScrollBar::moveVertical(const int & size)
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

		int X = barPOS.x + FRAME_SIZE;
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
		int Y = barPOS.y + FRAME_SIZE;

		for (auto & bt : buttons) {
			bt.setPosition({ X, Y, width, height });
			Y += height;
		}
		setWidthHeight(X, Y);
	}
}
