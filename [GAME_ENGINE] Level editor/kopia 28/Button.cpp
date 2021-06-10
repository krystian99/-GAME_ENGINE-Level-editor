#include "Button.h"
#include "Mouse.h"
#include "Video_Info.h"
#include "Renderer.h"

Button::Button(const SDL_Rect & pos) :
	clicked{ false },
	mouse_over{ false },
	l_bt_pressing{ false }
{
	position.x = std::round(pos.x * Video_Info::get_scaleW());
	position.y = std::round(pos.y * Video_Info::get_scaleH());
	position.w = std::round(pos.w * Video_Info::get_scaleW());
	position.h = std::round(pos.h * Video_Info::get_scaleH());
}

void Button::render()
{
	SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::get(), &position);
	//tX.render(nullptr, &position);
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}

void Button::events()
{
	mouse_handler();
}

void Button::set_position(const int & render_X, const int & render_Y)
{
	position.x = render_X;
	position.y = render_Y;
}

void Button::mouse_handler()
{
	clicked = false;
	mouse_over = false;

	if (Mouse::getX() >= position.x && Mouse::getX() <= position.x + position.w
		&& Mouse::getY() >= position.y && Mouse::getY() <= position.y + position.h)
	{
		mouse_over = true;
		onMouseOver(); // gdy myszka jest na pozycji przycisku
		if (Mouse::is_pressedL())
			l_bt_pressing = true;
		else if (!Mouse::is_pressedL() && l_bt_pressing) {
			clicked = true;
			onClick();
			l_bt_pressing = false;
		}
	}
	else l_bt_pressing = false;
}

void Button::load_background(std::string path)
{
	//tX.loadFromFile(path);
}