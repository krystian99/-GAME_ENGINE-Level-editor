#include "ScrollBar.h"
#include "Mouse.h"
#include "Setup.h"
#include "Buttons_resources.h"

/*// TEST
#include <iostream>
using std::cout;
using std::endl;
// END TEST*/
Texture ScrollBar::background{};
SDL_Rect ScrollBar::barPOS{};
int ScrollBar::button_width{};
int ScrollBar::button_height = 90;
ScrollBar::ScrollBar(ButtonType_LC type) :
	button_type{ type }
{}

void ScrollBar::load_images()
{
	setButtons_LC();
}

void ScrollBar::render(SDL_Renderer * rn)
{
	background.render(rn, nullptr, &barPOS);
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

void ScrollBar::Init(const SDL_Rect & position, const double & scaleW, const double & scaleH) // inicjuje wszystkie sk³adniki, ustawia pozycje przycisków i scrollbara
{
	button_height *= scaleH;
	barPOS = { position.x, position.y, position.w, position.h };
	background.loadFromFile("files/ScrollBarsTX/background.png"); // ³aduje t³o ScrollBara
}

void ScrollBar::InitButtons()
{
	switch (button_type) {
	case ButtonType_LC::DYNAMIC:
		buttons.reserve(Buttons_TX::Dynamic_textures.size());
		buttons.resize(Buttons_TX::Dynamic_textures.size());
		break;
	case ButtonType_LC::KEY:
		buttons.reserve(Buttons_TX::Key_textures.size());
		buttons.resize(Buttons_TX::Key_textures.size());
		break;
	case ButtonType_LC::STATIC:
		buttons.reserve(Buttons_TX::Static_textures.size());
		buttons.resize(Buttons_TX::Static_textures.size());
		break;
	}
	load_images();
	setStartButtonPOS();
}

void ScrollBar::events(SDL_Renderer * rn)
{
	mouse_handler();
	render(rn);
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
		buttons_render_vertical(rn, bt);
	}
}

void ScrollBar::buttons_render_vertical(SDL_Renderer * rn, Button_LC & bt) // b³¹d - jeden przycisk wgl siê nie renderuje
{
	const SDL_Rect * tmp = bt.getPOS();
	SDL_Rect clip; // obszar textury przycisku

	if (tmp->y >= barPOS.y + FRAME_SIZE && tmp->y + tmp->h <= barPOS.y + barPOS.h - FRAME_SIZE)
		bt.render(rn);

	else if (tmp->y < barPOS.y + FRAME_SIZE && tmp->y + tmp->h > barPOS.y + FRAME_SIZE) {

		int rendered_part = tmp->y + tmp->h - (barPOS.y + FRAME_SIZE);

		//double scaleY = double(rendered_part) / double(tmp->h);

		int startY = bt.getTX_Height();// *scaleY;

		clip = { tmp->x, barPOS.y + FRAME_SIZE, tmp->w, tmp->y + tmp->h - (barPOS.y + FRAME_SIZE) };
		//bt.render(rn, &clip);
		bt.render(rn, 0, /*startY*/0, &clip);
	}

	else if (tmp->y < barPOS.y + barPOS.h - FRAME_SIZE && tmp->y + tmp->h > barPOS.y + barPOS.h - FRAME_SIZE) {
		clip = { tmp->x, tmp->y, tmp->w, barPOS.y + barPOS.h - FRAME_SIZE - tmp->y };

		int rendered_part = barPOS.y + barPOS.h - FRAME_SIZE - tmp->y;

		int start_scaleY = rendered_part / tmp->h;

		//bt.render(rn, &clip);
		bt.render(rn, 0, 0, &clip);
	}
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
	setButtonsPOS_vertical(size);
}

void ScrollBar::setWidthHeight(const int & width, const int & height)
{
	buttons_pos = { barPOS.x + FRAME_SIZE, barPOS.y + FRAME_SIZE, width, height };
}

void ScrollBar::setButtons_LC()
{
	switch (button_type) {
	case ButtonType_LC::STATIC:
		for (int i = 0; i < buttons.size(); i++)
			buttons[i].loadTX(Buttons_TX::Static_textures[i]);
		break;
	case ButtonType_LC::DYNAMIC:
		for (int i = 0; i < buttons.size(); i++)
			buttons[i].loadTX(Buttons_TX::Dynamic_textures[i]);
		break;
	case ButtonType_LC::KEY:
		for (int i = 0; i < buttons.size(); i++)
			buttons[i].loadTX(Buttons_TX::Key_textures[i]);
		break;
	}
}

void ScrollBar::moveHorizontal(const int & size)
{
	int X = buttons_pos.currentStartX;
	int Y = buttons_pos.currentStartY;

	for (auto & bt : buttons) {
		bt.setPosition({ X + size, Y, button_width, button_height });
		X += button_width;
	}
	buttons_pos.currentStartX += size;
	buttons_pos.currentEndX += size;
}

void ScrollBar::moveVertical(const int & size)
{
	int X = buttons_pos.currentStartX;
	int Y = buttons_pos.currentStartY;

	for (auto & bt : buttons) {
		bt.setPosition({ X, Y + size, button_width, button_height });
		Y += button_height;
	}
	buttons_pos.currentStartY += size;
	buttons_pos.currentEndY += size;
}

void ScrollBar::setStartButtonPOS()
{
	button_width = barPOS.w - (2 * FRAME_SIZE);
	button_height = 90;

	int X = barPOS.x + FRAME_SIZE;
	int Y = barPOS.y + FRAME_SIZE;

	for (auto & bt : buttons) {
		bt.setPosition({ X, Y, button_width, button_height });
		Y += button_height;
	}
	setWidthHeight(X, Y);
}