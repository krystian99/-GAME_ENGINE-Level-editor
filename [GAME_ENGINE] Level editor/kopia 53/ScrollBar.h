#pragma once
#include <vector>
#include "Button.h"
#include "Texture.h"

class ScrollBar
{
	enum class Render_state { COLOR, TEXTURE };
public:
	enum class ScrollBar_orient { HORIZONTAL, VERTICAL };

	ScrollBar(const SDL_Rect & pos, const std::string & texture, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default); // ustala automatycznie orientacjê
	ScrollBar(const SDL_Rect & pos, const SDL_Color & color, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default); // ustala automatycznie orientacjê
	ScrollBar(const SDL_Rect & pos, const SDL_Color & color, ScrollBar_orient ornt, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default); // spaceof -> iloœæ miejsca dla przycisku

	void events();
	void render();

	bool is_mouseOver() const { return mouse_over; }
	bool is_buttonClicked() const { return button_clicked; }

	void deactivate_buttons(); // deaktywuj wszystkie przyciski -> nie mo¿e byæ aktywnych wiêcej ni¿ jeden przycisk

	void update_about(int x, int y);

	void operator=(const std::vector<Button*> & btns);

	~ScrollBar() {}
private:
	ScrollBar(const SDL_Rect & pos, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default);

	void reset_states();

	void render_buttons();

	void move_all(int size_x, int size_y);

	void move_horizontal();
	void move_vertical();
private:
	SDL_Rect position;

	static const int Move_size = 22;

	static const int button_space_default = 5;

	int button_space, space_fromSide;

	int button_width, button_height;

	union { // unia anonimowa - ma tylko jeden adres, który jest zaalokowany jako najwiêkszy obiekt - tutaj sizeof(Texture) > sizeof(SDL_Color)
		SDL_Color colorBG;
		Texture textureBG; // background texture
	};

	Button * current_button{ nullptr };

	bool mouse_over{ false }, button_clicked{ false };

	ScrollBar_orient orient; // wyznaczane automatycznie albo rêcznie
	Render_state render_state;

	std::vector<Button*> buttons; // bazowy przycisk - mog¹ byæ umieszczone pochodne tego przycisku
};