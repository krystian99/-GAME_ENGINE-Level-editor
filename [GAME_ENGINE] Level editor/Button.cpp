#include "Button.h"
#include "Mouse.h"
#include "Video_Info.h"
#include "Renderer.h"

Button::Button(const SDL_Rect & pos)
{
	set_scaled_position(pos);
}

Button::Button(const SDL_Rect & pos, const std::string & texture) : 
	Button{ pos }
{
	tX.loadFromFile(texture);
}

Button::Button(const std::string & texture)
{
	tX.loadFromFile(texture);
}

Button::Button(const std::string & texture, Function on_click) :
	on_click_func{ on_click }
{
	tX.loadFromFile(texture);
}

Button::Button(const std::string & texture, Function on_click, Function on_mouse_over) : 
	Button{ texture, on_click }
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
	tX.render(nullptr, &getPOS());
}

void Button::render(const SDL_Rect & tX_area, const SDL_Rect & destination_area)
{
	tX.render(&tX_area, &destination_area);
}

void Button::set_active(bool b)
{
	if (!b)
		on_Deactivate();
	else 
		on_Activate();
	active = b;
}

void Button::events()
{
	Object::events();
}
void Button::set_texture(const std::string & path)
{
	tX.loadFromFile(path);
}

void Button::on_mouseL1hit()
{
	active = true;

	if (on_click_func)
		on_click_func();
}

void Button::on_mouseOver()
{
	tX.set_blendAlpha(alpha_mod_mouseOver);
}

void Button::on_mouseOut()
{
	tX.set_blendAlpha(alpha_mod_mouseOut);
}