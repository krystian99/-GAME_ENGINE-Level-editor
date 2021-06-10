#include "InputArea.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Setup.h"

void InputArea::Init(const SDL_Rect & rt, const int & size, const SDL_Color & color)
{
	position = rt;

	set_TextSize(size);
	set_TextColor(color);
	//
	input = "d";
	text.setTEXT(input);
	//
	text.loadFont("lazy.ttf", size, color);

	textPOS = { position.x, position.y, text.getWidth(), text.getHeight() };
	text.set_position(textPOS);
}

/*void InputArea::get()
{
	backspace_pressing = false;

	getLiters();
	getOthers();
}*/

void InputArea::render(SDL_Renderer * rn)
{
	background.render(rn, nullptr, &position);
	text.render(rn, position.x, text.getWidth());
}

void InputArea::events()
{
	/*background.render(rn, nullptr, &position);
	text.render(rn, position.x, text.getWidth());*/

	backspace_pressing = false;

	getLiters();
	getOthers();
}

void InputArea::set_TextSize(const int & size)
{
	text.setSize(size);
}

void InputArea::set_TextColor(const SDL_Color & color)
{
	text.setColor(color);
}

void InputArea::addBack(const char & c)
{
	if (Keyboard::getModState() == Key::SHIFT)
		input.push_back(toupper(c));
	else 
		input.push_back(tolower(c));
	updateTEXT();
}

void InputArea::updateTEXT()
{
	text.update(input);
	textPOS = { position.x, position.y, text.getWidth(), text.getHeight() };
	text.set_position(textPOS);
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
	if (Keyboard::getBackSpace() == Key::BACKSPACE){// && !backspace_pressing) {
		backspace_pressing = true;
		if (input.size()) {
			input.pop_back();
			if (!input.size())
				input = " ";
			updateTEXT();
		}
	}
	switch (Keyboard::getState())
	{
	/*case Key::BACKSPACE:
		if (input.size()) {
			input.pop_back();
			if (!input.size())
				input = " ";
			updateTEXT();
		}
		break;*/
	case Key::CAPS_LOCK:
		toggled_CapsLock = toggled_CapsLock == true ? false : true;
		break;
	case Key::SPACE:
		input.push_back(' ');
		break;
	}
}

void InputArea::mouse_handler()
{
	if (Mouse::getMousePOSx() >= position.x && Mouse::getMousePOSx() <= position.x + position.w
		&& Mouse::getMousePOSy() >= position.y && Mouse::getMousePOSy() <= position.y + position.h)
	{
		if (Mouse::getButtonState() == Mouse_key::L_BUTTON)
			l_bt_pressing = true;
		else if (Mouse::getButtonState() == Mouse_key::NONE && l_bt_pressing) {
			//state = InputArea_state::SELECTED;
			l_bt_pressing = false;
		}
	}
}
