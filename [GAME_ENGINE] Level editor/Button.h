#pragma once
#include "Texture.h"
#include "Object.h"
#include <memory>

// v1 - musi zostaæ w przysz³oœci zmienione - jak na razie zajmuje siê wa¿niejszymi sprawami(14.07.2016r.) 
// v2 - zmieniono i przebudowano ca³kowicie hierarchiê przycisków -> teraz wszystko dzia³a sprawnie i wszystko jest ³atwe w obs³udze
// oraz jest bardzo wygodne. Rozszerzalnoœæ stopieñ maximum (28.08.2016r.)

class Button;

using BButton_ptr = std::shared_ptr<Button>; // BButton -> bazowy przycisk dlatego zdublowane 'B'

class Button : public Object
{
protected:
	using Function = void(*)();
public:
	Button(const SDL_Rect & pos);
	Button(const SDL_Rect & pos, const std::string & texture);
	Button(const std::string & texture);
	Button(const std::string & texture, Function on_click);
	Button(const std::string & texture, Function on_click, Function on_mouse_over);
	Button(const SDL_Rect & pos, const std::string & texture, Function on_click);
	Button(const SDL_Rect & pos, const std::string & texture, Function on_click, Function on_mouse_over);

	virtual void render();
	virtual void render(const SDL_Rect & tX_area, const SDL_Rect & destination_area);

	bool is_active() const { return active; }
	void set_active(bool b);

	virtual void events();

	Texture & getTX() { return tX; } // zwróæ texturê w celu uzyskania informacji o szerokoœci lub d³ugoœci
	void set_texture(const std::string & path);

	virtual ~Button() {}
protected:
	void on_mouseL1hit() override; // jak na ten moment tylko to jest potrzebne

	void on_mouseOver() override;
	void on_mouseOut() override;

	virtual void on_Deactivate() {}
	virtual void on_Activate() {}
protected:
	Texture tX; // background texture
private:
	bool active{ false };

	Uint8 alpha_mod_mouseOut{ 255 };
	Uint8 alpha_mod_mouseOver{ 100 };

	Function on_click_func{ nullptr };
	Function on_mouse_over_func{ nullptr };
};