#include "Folder_button.h"

Texture Folder_button::button_fill{};

Folder_button::Folder_button(const char * dscrptn, const std::string & texture_path) :
	Button(texture_path)//, description{dscrptn}
{}

Folder_button::Folder_button(const char * dscrptn, const std::string & texture_path, Function on_click) :
	Button{ texture_path, on_click }
{

}

void Folder_button::events()
{
	Button::events();
}

void Folder_button::render()
{
	button_fill.render(nullptr, &getPOS()); // renderuj t³o
	Button::render();
}

void Folder_button::render(const SDL_Rect & tX_area, const SDL_Rect & destination_area)
{
	button_fill.render(&tX_area, &destination_area);
	Button::render(tX_area, destination_area);
}

void Folder_button::set_Texture(const std::string & str)
{
	button_fill.loadFromFile(str);
}

void Folder_button::onClick()
{
	Button::onClick();
}

void Folder_button::onMouseOver()
{

}