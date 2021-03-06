#pragma once
#include <string>
#include "Button.h"
#include "Text.h"

class Folder_button : public Button // tymczasowy przycisk do aktywacji
{
public:
	using Button::Button;
	//Folder_button(const char * dscrptn, const std::string & texture_path);
	//Folder_button(const char * dscrptn, const std::string & texture_path, Function on_click);

	void events();
	void render();
	void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);

	static void set_Texture(const std::string & str);

	~Folder_button() {}
protected:
	void on_mouseL1hit() override;

	void on_mouseOut() override;

	void on_Activate() override;
	void on_Deactivate() override;
private:
	static Texture button_fill;

	Uint8 alpha_modUnselected{ 255 };
	Uint8 alpha_modSelected{ 100 };
};