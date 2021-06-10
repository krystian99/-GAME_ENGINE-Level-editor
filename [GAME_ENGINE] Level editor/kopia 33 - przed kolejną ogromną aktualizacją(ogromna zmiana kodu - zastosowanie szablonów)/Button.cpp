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

Button::Button(const SDL_Rect & pos, const std::string & texture) : 
	Button{ pos }
{
	tX.loadFromFile(texture);
}

Button::Button(const std::string & texture) :
	position{},
	clicked{ false },
	mouse_over{ false },
	l_bt_pressing{ false }
{
	tX.loadFromFile(texture);
}

Button::Button(const std::string & texture, Function on_click) :
	on_click_func{ on_click }
{
	tX.loadFromFile(texture);
}

Button::Button(const std::string & texture, Function on_click, Function on_mouse_over)
	: Button{ texture, on_click }
{
	on_mouse_over_func = on_mouse_over;
}

Button::Button(const SDL_Rect & pos, const std::string & texture, Function on_click) :
	Button{ pos, texture }
{
	on_mouse_over_func = nullptr;
	on_click_func = on_click;
}

Button::Button(const SDL_Rect & pos, const std::string & texture, Function on_click, Function on_mouse_over) :
	Button{ pos, texture, on_click }
{
	on_mouse_over_func = on_mouse_over;
}

void Button::render()
{
	SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::get(), &position);
	tX.render(nullptr, &position);
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}

void Button::render(const SDL_Rect & tX_area, const SDL_Rect & destination_area)
{
	tX.render(&tX_area, &destination_area);
}

void Button::events()
{
	mouse_handler();
}

void Button::set_texture(const std::string & path)
{
	tX.loadFromFile(path);
}

void Button::update_position(const int & renderX, const int & renderY)
{
	position.x = renderX;
	position.y = renderY;
}

void Button::set_position(const SDL_Rect & pos) // przeskalowane wczeœniej
{
	position = pos; // pre-scaled
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

void Button::onMouseOver()
{
	if (on_mouse_over_func)
		on_mouse_over_func();
}

void Button::onClick()
{
	if (on_click_func)
		on_click_func();
}