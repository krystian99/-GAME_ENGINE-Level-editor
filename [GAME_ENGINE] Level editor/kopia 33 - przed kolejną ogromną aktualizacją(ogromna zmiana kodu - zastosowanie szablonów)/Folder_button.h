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

	~Folder_button() {}
private:
	void onClick();
	void onMouseOver();
private:
	//Text text;
	//std::string description;
};