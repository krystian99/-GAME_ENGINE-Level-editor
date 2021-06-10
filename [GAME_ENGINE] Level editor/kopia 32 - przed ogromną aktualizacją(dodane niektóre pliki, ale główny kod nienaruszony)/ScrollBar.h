#pragma once
#include <vector>
#include "Button.h"
#include "Texture.h"

class ScrollBar
{
	enum class ScrollBar_orient { HORIZONTAL, VERTICAL };
	enum class Render_state { COLOR, TEXTURE };
public:
	ScrollBar(const SDL_Rect & pos, const std::string & texture);
	ScrollBar(const SDL_Rect & pos, const SDL_Color & color);

	void events();
	void render();

	void operator=(const std::vector<Button*> & btns);

	~ScrollBar() {}
private:
	ScrollBar(const SDL_Rect & pos);

	void render_buttons();

	void move_horizontal();
	void move_vertical();
private:
	SDL_Rect position;

	static const int Move_size = 15;

	static const int button_space = 5;
	int button_width, button_height;

	union { // unia anonimowa - ma tylko jeden adres, który jest zaalokowany jako najwiêkszy obiekt - tutaj sizeof(Texture) > sizeof(SDL_Color)
		SDL_Color colorBG;
		Texture textureBG; // background texture
	};

	ScrollBar_orient orient; // wyznaczane automatycznie
	Render_state render_state;

	std::vector<Button*> buttons; // bazowy przycisk
};