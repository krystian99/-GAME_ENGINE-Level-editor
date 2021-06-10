#pragma once
#include "Texture.h"
#include "Object.h"

// v1 - musi zosta� w przysz�o�ci zmienione - jak na razie zajmuje si� wa�niejszymi sprawami(14.07.2016r.) 
// v2 - zmieniono i przebudowano ca�kowicie hierarchi� przycisk�w -> teraz wszystko dzia�a sprawnie i wszystko jest �atwe w obs�udze
// oraz jest bardzo wygodne. Rozszerzalno�� stopie� maximum (28.08.2016r.)

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

	const Texture & getTX() const { return tX; } // zwr�� textur� w celu uzyskania informacji o szeroko�ci lub d�ugo�ci
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