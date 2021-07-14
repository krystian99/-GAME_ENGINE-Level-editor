#pragma once
#include <vector>
#include "Button.h"
#include "Texture.h"
#include "Rect.h"
#include "Video_Info.h"
#include "Renderer.h"
#include "Mouse.h"
#include <cmath>
#include "Object.h"

enum class ScrollBar_orient { HORIZONTAL, VERTICAL };

template<enum class ScrollBar_orient scroolbarOrient>
class ScrollBar : public Object
{
	enum class Render_state { COLOR, TEXTURE };
public:
	ScrollBar(const SDL_Rect& pos, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default) :
		Object{ pos }
	{
		button_space = space_beetwen_buttons;
		this->space_fromSide = space_fromSide;

		set_scaled_position(pos);

		if (getW() > getH()) {
			orient = ScrollBar_orient::HORIZONTAL;
			button_height = getH() - 2 * space_fromSide;
			button_width = buttonSize_expand * Video_Info::get_scaleW();
		}
		else {
			orient = ScrollBar_orient::VERTICAL;
			button_width = getW() - 2 * space_fromSide; // dlatego 2 razy bo przy lewej i prawej krawêdzi ma byæ taki sama pusta przestrzeñ
			button_height = buttonSize_expand * Video_Info::get_scaleH();
		}
	}
	ScrollBar(const SDL_Rect& pos, const std::string& texture, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default) // ustala automatycznie orientacjê
		:
		ScrollBar{ pos, buttonSize_expand, space_beetwen_buttons, space_fromSide }
	{
		render_state = Render_state::TEXTURE;
		textureBG.loadFromFile(texture_path);
	}
	ScrollBar(const SDL_Rect& pos, const SDL_Color& color, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default) // ustala automatycznie orientacjê
		: ScrollBar{ pos, buttonSize_expand, space_beetwen_buttons, space_fromSide }
	{
		render_state = Render_state::COLOR;
		colorBG = color;
	}
	ScrollBar(const SDL_Rect& pos, const SDL_Color& color, ScrollBar_orient ornt, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default) // spaceof -> iloœæ miejsca dla przycisku
		: ScrollBar{ pos, color, buttonSize_expand, space_beetwen_buttons, space_fromSide }
	{

	}

	void events();
	void render();

	void reset();

	bool is_buttonClicked() const { return button_clicked; }

	void deactivate_buttons(); // deaktywuj wszystkie przyciski -> nie mo¿e byæ aktywnych wiêcej ni¿ jeden przycisk
	void deactivate_mouseOverEvent();

	void update(int x, int y);

	void operator=(const std::vector<BButton_ptr>& btns);

	~ScrollBar() {}
private:
	void on_mouseWheel_down_1hit() override;
	void on_mouseWheel_up_1hit() override;

	void reset_states();

	void move_all(int size_x, int size_y);
private:
	static const int Move_size = 22;

	static const int button_space_default = 5;

	int button_space, space_fromSide;

	int button_width, button_height;

	union { // unia anonimowa - ma tylko jeden adres, który jest zaalokowany jako najwiêkszy obiekt - tutaj sizeof(Texture) > sizeof(SDL_Color)
		SDL_Color colorBG;
		Texture textureBG; // background texture
	};

	Button* current_button{ nullptr };
	Button* current_mouseOver_button{ nullptr };

	bool button_clicked{ false };

	ScrollBar_orient orient; // wyznaczane automatycznie albo rêcznie
	Render_state render_state;

	std::vector<BButton_ptr> buttons; // bazowy przycisk - mog¹ byæ umieszczone pochodne tego przycisku
};

template<>
inline void ScrollBar<ScrollBar_orient::VERTICAL>::on_mouseWheel_down_1hit()
{
	int temp_moveSize;

	if (buttons.back()->get_position().y + buttons.back()->get_position().h > down() - space_fromSide) { // sprawdz czy mo¿na jeszcze przesun¹æ
		if (buttons.back()->get_position().y + buttons.back()->get_position().h - Move_size > down() - space_fromSide) {
			for (auto& button : buttons) {
				const SDL_Rect& pos = button->get_position(); // skrócenie identyfikatora
				button->set_position(pos.x, pos.y - Move_size);
			}
		}
		else {
			const SDL_Rect& pos = buttons.back()->get_position();
			temp_moveSize = pos.y + pos.h - (down() - space_fromSide);

			for (auto& button : buttons) {
				const SDL_Rect& pos = button->get_position(); // skrócenie identyfikatora
				button->set_position(pos.x, pos.y - temp_moveSize);
			}
		}
	}
}

template<>
inline void ScrollBar<ScrollBar_orient::VERTICAL>::on_mouseWheel_up_1hit()
{
	int temp_moveSize;

	if (buttons.front()->get_position().y < up() + space_fromSide) {
		if (buttons.front()->get_position().y + Move_size < up() + space_fromSide) {
			for (auto& button : buttons) {
				const SDL_Rect& pos = button->get_position();
				button->set_position(pos.x, pos.y + Move_size);
			}
		}
		else {
			const SDL_Rect& pos = buttons.front()->get_position();
			temp_moveSize = up() + space_fromSide - pos.y;

			for (auto& button : buttons) {
				const SDL_Rect& pos = button->get_position(); // skrócenie identyfikatora
				button->set_position(pos.x, pos.y + temp_moveSize);
			}
		}
	}
}

template<>
inline void ScrollBar<ScrollBar_orient::HORIZONTAL>::on_mouseWheel_down_1hit()
{
	int temp_moveSize;

	if (buttons.front()->get_position().x < left() + space_fromSide) {
		if (buttons.front()->get_position().x + Move_size < left() + space_fromSide) {
			for (auto& button : buttons) {
				const SDL_Rect& pos = button->get_position();
				button->set_position(pos.x + Move_size, pos.y);
			}
		}
		else {
			const SDL_Rect& pos = buttons.front()->get_position();
			temp_moveSize = left() + space_fromSide - pos.x;

			for (auto& button : buttons) {
				const SDL_Rect& pos = button->get_position(); // skrócenie identyfikatora
				button->set_position(pos.x + temp_moveSize, pos.y);
			}
		}
	}
}

template<>
inline void ScrollBar<ScrollBar_orient::HORIZONTAL>::on_mouseWheel_up_1hit()
{
	int temp_moveSize;

	if (buttons.back()->get_position().x + buttons.back()->get_position().w > right() - space_fromSide) { // sprawdz czy mo¿na jeszcze przesun¹æ
		if (buttons.back()->get_position().x + buttons.back()->get_position().w - Move_size > right() - space_fromSide) {
			for (auto& button : buttons) {
				const SDL_Rect& pos = button->get_position(); // skrócenie identyfikatora
				button->set_position(pos.x - Move_size, pos.y);
			}
		}
		else {
			const SDL_Rect& pos = buttons.back()->get_position();
			temp_moveSize = pos.x + pos.w - (right() - space_fromSide);

			for (auto& button : buttons) {
				const SDL_Rect& pos = button->get_position(); // skrócenie identyfikatora
				button->set_position(pos.x - temp_moveSize, pos.y);
			}
		}
	}
}

template <enum class ScrollBar_orient scroolbarOrient>
inline void ScrollBar<scroolbarOrient>::reset_states()
{
	button_clicked = false;
}


template <enum class ScrollBar_orient scroolbarOrient>
inline void ScrollBar<scroolbarOrient>::move_all(int size_x, int size_y)
{
	for (auto& button : buttons)
		button->update_position(size_x, size_y);
}

template <>
inline void ScrollBar<ScrollBar_orient::HORIZONTAL>::events()
{
	reset_states();

	Object::events();

	if (is_mouseOver())
	{
		for (auto& button : buttons) {

			button->events();

			if (button->is_mouseKey_1hit(Mouse_key::L_BUTTON)) {
				if (current_button)
					current_button->set_active(false);
				button_clicked = true;
				current_button = button.get();

				current_button->set_active(true);
				break;
			}
		}
	}
	//else
		//deactivate_mouseOverEvent(); // je¿eli pozosta³ przycisk, który wymaga usuniêcia flagi mouse_Over
}

template <>
inline void ScrollBar<ScrollBar_orient::VERTICAL>::events()
{
	reset_states(); 
	
	Object::events();


	if (is_mouseOver())
	{
		for (auto& button : buttons) {

			button->events();
			/*if (button->is_mouseOver())
				current_mouseOver_button = button.get();*/
			if (button->is_mouseKey_1hit(Mouse_key::L_BUTTON)) {
				if (current_button)
					current_button->set_active(false);
				button_clicked = true;
				current_button = button.get();

				current_button->set_active(true);
				break;
			}
		}
	}
	//else
		//deactivate_mouseOverEvent(); // je¿eli pozosta³ przycisk, który wymaga usuniêcia flagi mouse_Over
}

template <>
inline void ScrollBar<ScrollBar_orient::HORIZONTAL>::render()
{
	switch (render_state)
	{
	case Render_state::TEXTURE:
		textureBG.render(nullptr, &get_position());
		break;
	case Render_state::COLOR:
		Renderer::set_renderColor(colorBG);
		SDL_RenderFillRect(Renderer::get(), &get_position());
		Renderer::set_defaultColor();
		break;
	}

	static SDL_Rect temp_pos, texture_area;

	for (auto& button : buttons) {
		auto& pos = button->get_position();

		if (pos.x >= left() + space_fromSide && pos.x + pos.w <= right() - space_fromSide)
			button->render(); // renderuj ca³y przycisk
		else if (pos.x < left() + space_fromSide && pos.x + pos.w > left() + space_fromSide) {
			temp_pos = { left() + space_fromSide, up() + space_fromSide, pos.x + pos.w - (left() + space_fromSide) , pos.h };

			auto& tX = button->getTX();

			double scale = double(temp_pos.w) / double(pos.w);

			texture_area.x = tX.getWidth() - std::round(tX.getWidth() * scale);
			texture_area.y = 0;
			texture_area.w = tX.getWidth() - texture_area.x;
			texture_area.h = tX.getHeight();

			button->render(texture_area, temp_pos);
		}
		else if (pos.x + pos.w > right() - space_fromSide && pos.x <= right() - space_fromSide) {
			temp_pos = { pos.x, up() + space_fromSide, right() - space_fromSide - pos.x, pos.h };

			auto& tX = button->getTX();

			double scale = double(temp_pos.w) / double(pos.w);

			texture_area.x = 0;
			texture_area.y = 0;
			texture_area.w = std::round(tX.getWidth() * scale);
			texture_area.h = tX.getHeight();

			button->render(texture_area, temp_pos);
		}
	}
}

template <>
inline void ScrollBar<ScrollBar_orient::VERTICAL>::render()
{
	switch (render_state)
	{
	case Render_state::TEXTURE:
		textureBG.render(nullptr, &get_position());
		break;
	case Render_state::COLOR:
		Renderer::set_renderColor(colorBG);
		SDL_RenderFillRect(Renderer::get(), &get_position());
		Renderer::set_defaultColor();
		break;
	}

	static SDL_Rect temp_pos, texture_area;

	for (auto& button : buttons) {
		auto& pos = button->get_position();

		if (pos.y >= up() + space_fromSide && pos.y + pos.h <= down() - space_fromSide)
			button->render();
		else if (pos.y < up() + space_fromSide && pos.y + pos.h > up() + space_fromSide) {
			temp_pos = { left() + space_fromSide, up() + space_fromSide, pos.w, pos.y + pos.h - (up() + space_fromSide) };

			auto& tX = button->getTX();

			double scale = double(temp_pos.h) / double(pos.h);

			texture_area.x = 0;
			texture_area.y = tX.getHeight() - std::round(tX.getHeight() * scale);
			texture_area.w = tX.getWidth();
			texture_area.h = tX.getHeight() - texture_area.y;

			button->render(texture_area, temp_pos);
		}
		else if (pos.y + pos.h > down() - space_fromSide && pos.y <= down() - space_fromSide) {
			temp_pos = { left() + space_fromSide, pos.y, pos.w, down() - space_fromSide - pos.y };

			auto& tX = button->getTX();

			double scale = double(temp_pos.h) / double(pos.h);

			texture_area.x = 0;
			texture_area.y = 0;
			texture_area.w = tX.getWidth();
			texture_area.h = std::round(tX.getHeight() * scale);

			button->render(texture_area, temp_pos);
		}
	}
}

template <enum class ScrollBar_orient scroolbarOrient>
inline void ScrollBar<scroolbarOrient>::reset()
{
	if (current_button)
		current_button->set_active(false);
}

template <enum class ScrollBar_orient scroolbarOrient>
inline void ScrollBar<scroolbarOrient>::deactivate_buttons()
{
	if (current_button) {
		current_button->set_active(false);
		current_button = nullptr;
	}
}

template <enum class ScrollBar_orient scroolbarOrient>
inline void ScrollBar<scroolbarOrient>::deactivate_mouseOverEvent()
{
	if (current_mouseOver_button) {
		if (!current_mouseOver_button->is_active()) {
			current_mouseOver_button->mouseOver_deactivate();
			current_mouseOver_button = nullptr;
		}
	}
}

template <enum class ScrollBar_orient scroolbarOrient>
inline void ScrollBar<scroolbarOrient>::update(int x, int y) // przesuñ ca³y ScrollBar w³¹cznie ze wszystkimi przyciskami
{
	updateX(x);
	updateY(y);

	move_all(x, y); // zaktualizuj pozycjê przycisków
}

template <>
inline void ScrollBar<ScrollBar_orient::HORIZONTAL>::operator=(const std::vector<BButton_ptr>& btns) // automatycznie ustala pozycje przycisków
{
	buttons = std::move(btns);

	int x = getX() + space_fromSide;
	int y = getY() + space_fromSide;

	for (auto& button : buttons) {
		button->set_position({ x, y, button_width, button_height });
		x += button_width + button_space;
	}
}

template <>
inline void ScrollBar<ScrollBar_orient::VERTICAL>::operator=(const std::vector<BButton_ptr>& btns) // automatycznie ustala pozycje przycisków
{
	buttons = std::move(btns);

	int x = getX() + space_fromSide;
	int y = getY() + space_fromSide;

	for (auto& button : buttons) {
		button->set_position({ x, y, button_width, button_height });
		y += button_height + button_space;
	}
}
