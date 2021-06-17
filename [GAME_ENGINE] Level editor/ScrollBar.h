#pragma once
#include <vector>
#include "Button.h"
#include "Texture.h"
#include "Rect.h"
//#include <SDL_rect.h>

class Button;
class Rect;
class Texture;

enum class ScrollBar_orient { HORIZONTAL, VERTICAL };
enum class Render_state { COLOR, TEXTURE };

template<enum class ScrollBar_orient scroolbarOrient>
class ScrollBar
{
	//enum class Render_state { COLOR, TEXTURE };
public:

	ScrollBar(const SDL_Rect &pos, const std::string & texture, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default); // ustala automatycznie orientacj�
	ScrollBar(const SDL_Rect & pos, const SDL_Color & color, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default); // ustala automatycznie orientacj�
	ScrollBar(const SDL_Rect & pos, const SDL_Color & color, ScrollBar_orient ornt, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default); // spaceof -> ilo�� miejsca dla przycisku

	void events();
	void render();

	void reset();

	bool is_mouseOver() const { return mouse_over; }
	bool is_buttonClicked() const { return button_clicked; }

	void deactivate_buttons(); // deaktywuj wszystkie przyciski -> nie mo�e by� aktywnych wi�cej ni� jeden przycisk
	void deactivate_mouseOverEvent();

	void update_about(int x, int y);

	void operator=(const std::vector<BButton_ptr> & btns);

	~ScrollBar() {}
private:
	ScrollBar(const SDL_Rect & pos, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default);

	void render_horizontal();
	void render_vertical();

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

	union { // unia anonimowa - ma tylko jeden adres, kt�ry jest zaalokowany jako najwi�kszy obiekt - tutaj sizeof(Texture) > sizeof(SDL_Color)
		SDL_Color colorBG;
		Texture textureBG; // background texture
	};

	Button * current_button{ nullptr };
	Button * current_mouseOver_button{ nullptr };

	bool mouse_over{ false }, button_clicked{ false };

	ScrollBar_orient orient; // wyznaczane automatycznie albo r�cznie
	Render_state render_state;

	std::vector<BButton_ptr> buttons; // bazowy przycisk - mog� by� umieszczone pochodne tego przycisku
};
