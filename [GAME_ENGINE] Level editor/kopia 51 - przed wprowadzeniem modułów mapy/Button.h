#pragma once
#include "Texture.h"
#include "Object.h"

// v1 - musi zostaæ w przysz³oœci zmienione - jak na razie zajmuje siê wa¿niejszymi sprawami(14.07.2016r.) 
// v2 - zmieniono i przebudowano ca³kowicie hierarchiê przycisków -> teraz wszystko dzia³a sprawnie i wszystko jest ³atwe w obs³udze
// oraz jest bardzo wygodne. Rozszerzalnoœæ stopieñ maximum (28.08.2016r.)

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

	const Texture & getTX() const { return tX; } // zwróæ texturê w celu uzyskania informacji o szerokoœci lub d³ugoœci
	void set_texture(const std::string & path);

	virtual ~Button() {}
protected:
	void on_mouseL1hit() override; // jak na ten moment tylko to jest potrzebne

	virtual void on_Deactivate() {}
	virtual void on_Activate() {}
protected:
	Texture tX; // background texture
private:
	bool active{ false };

	Function on_click_func{ nullptr };
	Function on_mouse_over_func{ nullptr };
};