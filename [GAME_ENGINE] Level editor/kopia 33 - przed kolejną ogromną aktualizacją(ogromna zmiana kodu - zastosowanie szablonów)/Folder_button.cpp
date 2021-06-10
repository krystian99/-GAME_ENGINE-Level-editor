#include "Folder_button.h"

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
	Button::render();
}

void Folder_button::onClick()
{
	Button::onClick();
}

void Folder_button::onMouseOver()
{

}