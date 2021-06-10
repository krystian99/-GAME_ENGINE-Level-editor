#pragma once
#include <string>
#include "Button.h"
#include "Text.h"

class Folder_button : public Button
{
public:
	Folder_button(const char * dscrptn, const std::string & texture_path);
	Folder_button(const char * dscrptn, const std::string & texture_path, Function on_click);

	void events();
	void render();
	void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);

	static void set_Texture(const std::string & str);

	~Folder_button() {}
private:
	void onClick();
	void onMouseOver();
private:
	static Texture button_fill;
	//Text text;
	//std::string description;
};