#pragma once
#include <vector>
#include "Button.h"
#include "Texture.h"

class ScrollBar
{
	enum class Render_state { COLOR, TEXTURE };
public:
	enum class ScrollBar_orient { HORIZONTAL, VERTICAL };

	ScrollBar(const SDL_Rect & pos, const std::string & texture, int size_expand); // ustala automatycznie orientacj�
	ScrollBar(const SDL_Rect & pos, const SDL_Color & color, int size_expand); // ustala automatycznie orientacj�
	ScrollBar(const SDL_Rect & pos, const SDL_Color & color, ScrollBar_orient ornt, int size_expand);

	void events();
	void render();

	void operator=(const std::vector<Button*> & btns);

	~ScrollBar() {}
private:
	ScrollBar(const SDL_Rect & pos, int size_expand);

	void render_buttons();

	void move_horizontal();
	void move_vertical();
private:
	SDL_Rect position;

	static const int Move_size = 22;

	static const int button_space = 5;
	int button_width, button_height;

	union { // unia anonimowa - ma tylko jeden adres, kt�ry jest zaalokowany jako najwi�kszy obiekt - tutaj sizeof(Texture) > sizeof(SDL_Color)
		SDL_Color colorBG;
		Texture textureBG; // background texture
	};

	ScrollBar_orient orient; // wyznaczane automatycznie albo r�cznie
	Render_state render_state;

	std::vector<Button*> buttons; // bazowy przycisk - mog� by� umieszczone pochodne tego przycisku
};