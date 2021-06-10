#include "InputArea.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Setup.h"
#include "Video_Info.h"
#include "Renderer.h"
#include <cctype>

InputArea::InputArea(const SDL_Rect & pos, const int & startX, const int & startY, const std::string & font_path, int size_text, const SDL_Color & color_text, bool Digit_enabled, bool Alpha_enabled) :
	text{ startX, startY , font_path, size_text, color_text }, 
	digits_enabled{ Digit_enabled }, alpha_enabled{ Alpha_enabled }
{
	position = pos;
	Video_Info::set_scaledSize(position);
}

InputArea::InputArea(SDL_Renderer * rn, const SDL_Rect & pos, const int & startX, const int & startY, const std::string & font_path, int size_text, const SDL_Color & color_text, bool Digit_enabled, bool Alpha_enabled) :
	InputArea{ pos, startX, startY, font_path, size_text, color_text, Digit_enabled, Alpha_enabled }
{
	this->rn = rn;
}

void InputArea::render()
{
	if (!rn) {
		SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
		SDL_RenderDrawRect(Renderer::get(), &position);
		SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);

		if (!empty)
			text.render(position.x, text.getWidth());
	}
	else {
		SDL_SetRenderDrawColor(rn, 255, 0, 0, 255);
		SDL_RenderDrawRect(rn, &position);
		SDL_SetRenderDrawColor(rn, 255, 255, 255, 255);

		if (!empty)
			text.render(rn, position.x, text.getWidth());
	}
}

void InputArea::render(SDL_Renderer * rn)
{
	SDL_SetRenderDrawColor(rn, 255, 0, 0, 255);
	SDL_RenderDrawRect(rn, &position);
	SDL_SetRenderDrawColor(rn, 255, 255, 255, 255);

	if (!empty)
		text.render(rn, position.x, text.getWidth());
}

void InputArea::events()
{
	backspace_pressing = false;

	mouse_handler();

	if (current) 
	{
		if (Keyboard::getState() != Key::NONE) {
			if (alpha_enabled)
				getLiters();
			getOthers();
			if (digits_enabled)
				getDigits();
		}
	}
}

void InputArea::load_background(const std::string & d)
{
	if (rn)
		background.loadFromFile(rn, d);
	else
		background.loadFromFile(d);
}

void InputArea::addBack(const char & c)
{
	keyboard = SDL_GetKeyboardState(nullptr);

	empty = false;
	if (keyboard[SDL_SCANCODE_LSHIFT] || keyboard[SDL_SCANCODE_RSHIFT] || Keyboard::is_CapsLock_toggled())//if (Keyboard::getModState() == Key::SHIFT)
		input.push_back(toupper(c));
	else 
		input.push_back(tolower(c));
	updateTEXT();
}

void InputArea::updateTEXT()
{
	if (rn)
		text.update(rn, input);
	else
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