#include "InputArea.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Setup.h"
#include "Video_Info.h"
#include "Renderer.h"
#include <cctype>

InputArea::InputArea(const SDL_Rect & pos, const int & startX, const int & startY, const std::string & font_path, int size_text, const SDL_Color & color_text) :
	empty{ true },
	current{ false },
	clicked{ false },
	text{ startX, startY , font_path, size_text, color_text }
{
	position.x = round(Video_Info::get_scaleW() * pos.x);
	position.y = round(Video_Info::get_scaleH() * pos.y);
	position.w = round(Video_Info::get_scaleW() * pos.w);
	position.h = round(Video_Info::get_scaleH() * pos.h);
}

void InputArea::render()
{
	SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::get(), &position);
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);

	if (!empty)
		text.render(position.x, text.getWidth());
}

void InputArea::events()
{
	backspace_pressing = false;

	mouse_handler();

	if (current) {
		getLiters();
		getOthers();
		getDigits();
	}
}

void InputArea::load_background(const std::string & d)
{
	background.loadFromFile(d);
}

void InputArea::addBack(const char & c)
{
	empty = false;
	if (Keyboard::getModState() == Key::SHIFT)
		input.push_back(toupper(c));
	else 
		input.push_back(tolower(c));
	updateTEXT();
}

void InputArea::updateTEXT()
{
	text.update(input);
}

void InputArea::getLiters()
{
	switch (Keyboard::getState())
	{
	case Key::A:
		addBack('A');
		break;
	case Key::B:
		addBack('B');
		break;
	case Key::C:
		addBack('C');
		break;
	case Key::D:
		addBack('D');
		break;
	case Key::E:
		addBack('E');
		break;
	case Key::F:
		addBack('F');
		break;
	case Key::G:
		addBack('G');
		break;
	case Key::H:
		addBack('H');
		break;
	case Key::I:
		addBack('I');
		break;
	case Key::J:
		addBack('J');
		break;
	case Key::K:
		addBack('K');
		break;
	case Key::L:
		addBack('L');
		break;
	case Key::M:
		addBack('M');
		break;
	case Key::N:
		addBack('N');
		break;
	case Key::O:
		addBack('O');
		break;
	case Key::P:
		addBack('P');
		break;
	case Key::Q:
		addBack('Q');
		break;
	case Key::R:
		addBack('R');
		break;
	case Key::S:
		addBack('S');
		break;
	case Key::T:
		addBack('T');
		break;
	case Key::U:
		addBack('U');
		break;
	case Key::V:
		addBack('V');
		break;
	case Key::W:
		addBack('W');
		break;
	case Key::X:
		addBack('X');
		break;
	case Key::Y:
		addBack('Y');
		break;
	case Key::Z:
		addBack('Z');
		break;
	}
}

void InputArea::getOthers()
{
	if (Keyboard::getBackSpace() == Key::BACKSPACE){
		backspace_pressing = true;
		if (input.size()) {
			input.pop_back();
			if (!input.size())
				empty = true;
			else 
				updateTEXT();
		}
	}
	switch (Keyboard::getState())
	{
	case Key::CAPS_LOCK:
		toggled_CapsLock = !toggled_CapsLock;
		break;
	case Key::SPACE:
		input.push_back(' ');
		break;
	}
}

void InputArea::getDigits()
{
	switch (Keyboard::getState())
	{
	case Key::n0:
		addBack('0');
		break;
	case Key::n1:
		addBack('1');
		break;
	case Key::n2:
		addBack('2');
		break;
	case Key::n3:
		addBack('3');
		break;
	case Key::n4:
		addBack('4');
		break;
	case Key::n5:
		addBack('5');
		break;
	case Key::n6:
		addBack('6');
		break;
	case Key::n7:
		addBack('7');
		break;
	case Key::n8:
		addBack('8');
		break;
	case Key::n9:
		addBack('9');
		break;
	}
}

void InputArea::mouse_handler()
{
	clicked = false;
	if (Mouse::getX() >= position.x && Mouse::getX() <= position.x + position.w
		&& Mouse::getY() >= position.y && Mouse::getY() <= position.y + position.h)
	{
		clicked = true;
	}
}

void InputArea::reset()
{
	empty = true;
	input.clear();
}

void InputArea::setCurrent(bool x)
{
	current = x;
}