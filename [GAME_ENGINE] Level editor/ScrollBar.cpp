#include "ScrollBar.h"
#include "Video_Info.h"
#include "Renderer.h"
#include "Mouse.h"
#include <cmath>

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
ScrollBar<scroolbarOrient, renderState>::ScrollBar(const SDL_Rect& pos, const std::string& texture, int buttonSize_expand, int space_beetwen_buttons = button_space_default, int space_fromSide = button_space_default) :
	ScrollBar{ pos, buttonSize_expand, space_beetwen_buttons, space_fromSide }
{
	this->render_state = Render_state::TEXTURE;
	textureBG.loadFromFile(texture_path);
}


template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
ScrollBar<scroolbarOrient, renderState>::ScrollBar(const SDL_Rect& pos, const SDL_Color& color, int buttonSize_expand, int space_beetwen_buttons, int space_fromSide) :
	ScrollBar{ pos, buttonSize_expand, space_beetwen_buttons, space_fromSide }
{
	this->render_state = Render_state::COLOR;
	colorBG = color;
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
ScrollBar<scroolbarOrient, renderState>::ScrollBar(const SDL_Rect& pos, const SDL_Color& color, ScrollBar_orient ornt, int buttonSize_expand, int space_beetwen_buttons, int space_fromSide) :
	ScrollBar{ pos, color, buttonSize_expand, space_beetwen_buttons, space_fromSide }
{

}
template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
ScrollBar<scroolbarOrient, renderState>::ScrollBar(const SDL_Rect& pos, int buttonSize_expand, int space_beetwen_buttons, int space_fromSide)
{
	button_space = space_beetwen_buttons;
	this->space_fromSide = space_fromSide;

	position.x = std::round(pos.x * Video_Info::get_scaleW());
	position.y = std::round(pos.y * Video_Info::get_scaleH());
	position.w = std::round(pos.w * Video_Info::get_scaleW());
	position.h = std::round(pos.h * Video_Info::get_scaleH());

	if (position.w > position.h) {
		orient = ScrollBar_orient::HORIZONTAL;
		button_height = position.h - 2 * space_fromSide;
		button_width = buttonSize_expand * Video_Info::get_scaleW();
	}
	else {
		orient = ScrollBar_orient::VERTICAL;
		button_width = position.w - 2 * space_fromSide; // dlatego 2 razy bo przy lewej i prawej krawêdzi ma byæ taki sama pusta przestrzeñ
		button_height = buttonSize_expand * Video_Info::get_scaleH();
	}
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::render_horizontal()
{

}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::render_vertical()
{

}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::reset_states()
{
	mouse_over = false;
	button_clicked = false;
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::render_buttons()
{
	static SDL_Rect temp_pos, texture_area;

	switch (orient) {
	case ScrollBar_orient::HORIZONTAL: // nie zosta³o ukoñczone
		for (auto& button : buttons) {
			auto& pos = button->getPOS();

			if (pos.x >= position.x + space_fromSide && pos.x + pos.w <= position.x + position.w - space_fromSide)
				button->render(); // renderuj ca³y przycisk
			else if (pos.x < position.x + space_fromSide && pos.x + pos.w > position.x + space_fromSide) {
				temp_pos = { position.x + space_fromSide, position.y + space_fromSide, pos.x + pos.w - (position.x + space_fromSide) , pos.h };

				auto& tX = button->getTX();

				double scale = double(temp_pos.w) / double(pos.w);

				texture_area.x = tX.getWidth() - std::round(tX.getWidth() * scale);
				texture_area.y = 0;
				texture_area.w = tX.getWidth() - texture_area.x;
				texture_area.h = tX.getHeight();

				button->render(texture_area, temp_pos);
			}
			else if (pos.x + pos.w > position.x + position.w - space_fromSide && pos.x <= position.x + position.w - space_fromSide) {
				temp_pos = { pos.x, position.y + space_fromSide, position.x + position.w - space_fromSide - pos.x, pos.h };

				auto& tX = button->getTX();

				double scale = double(temp_pos.w) / double(pos.w);

				texture_area.x = 0;
				texture_area.y = 0;
				texture_area.w = std::round(tX.getWidth() * scale);
				texture_area.h = tX.getHeight();

				button->render(texture_area, temp_pos);
			}
		}
		break;
	case ScrollBar_orient::VERTICAL: // dzia³a perfekcyjnie
		for (auto& button : buttons) {
			auto& pos = button->getPOS();

			if (pos.y >= position.y + space_fromSide && pos.y + pos.h <= position.y + position.h - space_fromSide)
				button->render();
			else if (pos.y < position.y + space_fromSide && pos.y + pos.h > position.y + space_fromSide) {
				temp_pos = { position.x + space_fromSide, position.y + space_fromSide, pos.w, pos.y + pos.h - (position.y + space_fromSide) };

				auto& tX = button->getTX();

				double scale = double(temp_pos.h) / double(pos.h);

				texture_area.x = 0;
				texture_area.y = tX.getHeight() - std::round(tX.getHeight() * scale);
				texture_area.w = tX.getWidth();
				texture_area.h = tX.getHeight() - texture_area.y;

				button->render(texture_area, temp_pos);
			}
			else if (pos.y + pos.h > position.y + position.h - space_fromSide && pos.y <= position.y + position.h - space_fromSide) {
				temp_pos = { position.x + space_fromSide, pos.y, pos.w, position.y + position.h - space_fromSide - pos.y };

				auto& tX = button->getTX();

				double scale = double(temp_pos.h) / double(pos.h);

				texture_area.x = 0;
				texture_area.y = 0;
				texture_area.w = tX.getWidth();
				texture_area.h = std::round(tX.getHeight() * scale);

				button->render(texture_area, temp_pos);
			}
		}
		ScrollBar_orient::HORIZONTAL
			break;
	}
}
//#pragma warning(disable: 175)
/*template <>
void ScrollBar<ScrollBar_orient::HORIZONTAL, Render_state::TEXTURE>::render_buttons()
{
	static SDL_Rect temp_pos, texture_area;

	for (auto& button : buttons) {
		auto& pos = button->getPOS();

		if (pos.x >= position.x + space_fromSide && pos.x + pos.w <= position.x + position.w - space_fromSide)
			button->render(); // renderuj ca³y przycisk
		else if (pos.x < position.x + space_fromSide && pos.x + pos.w > position.x + space_fromSide) {
			temp_pos = { position.x + space_fromSide, position.y + space_fromSide, pos.x + pos.w - (position.x + space_fromSide) , pos.h };

			auto& tX = button->getTX();

			double scale = double(temp_pos.w) / double(pos.w);

			texture_area.x = tX.getWidth() - std::round(tX.getWidth() * scale);
			texture_area.y = 0;
			texture_area.w = tX.getWidth() - texture_area.x;
			texture_area.h = tX.getHeight();

			button->render(texture_area, temp_pos);
		}
		else if (pos.x + pos.w > position.x + position.w - space_fromSide && pos.x <= position.x + position.w - space_fromSide) {
			temp_pos = { pos.x, position.y + space_fromSide, position.x + position.w - space_fromSide - pos.x, pos.h };

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
void ScrollBar<ScrollBar_orient::HORIZONTAL, Render_state::COLOR>::render_buttons()
{
	static SDL_Rect temp_pos, texture_area;

	for (auto& button : buttons) {
		auto& pos = button->getPOS();

		if (pos.x >= position.x + space_fromSide && pos.x + pos.w <= position.x + position.w - space_fromSide)
			button->render(); // renderuj ca³y przycisk
		else if (pos.x < position.x + space_fromSide && pos.x + pos.w > position.x + space_fromSide) {
			temp_pos = { position.x + space_fromSide, position.y + space_fromSide, pos.x + pos.w - (position.x + space_fromSide) , pos.h };

			auto& tX = button->getTX();

			double scale = double(temp_pos.w) / double(pos.w);

			texture_area.x = tX.getWidth() - std::round(tX.getWidth() * scale);
			texture_area.y = 0;
			texture_area.w = tX.getWidth() - texture_area.x;
			texture_area.h = tX.getHeight();

			button->render(texture_area, temp_pos);
		}
		else if (pos.x + pos.w > position.x + position.w - space_fromSide && pos.x <= position.x + position.w - space_fromSide) {
			temp_pos = { pos.x, position.y + space_fromSide, position.x + position.w - space_fromSide - pos.x, pos.h };

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
void ScrollBar<ScrollBar_orient::VERTICAL, Render_state::TEXTURE>::render_buttons()
{
	static SDL_Rect temp_pos, texture_area;

	for (auto& button : buttons) {
		auto& pos = button->getPOS();

		if (pos.y >= position.y + space_fromSide && pos.y + pos.h <= position.y + position.h - space_fromSide)
			button->render();
		else if (pos.y < position.y + space_fromSide && pos.y + pos.h > position.y + space_fromSide) {
			temp_pos = { position.x + space_fromSide, position.y + space_fromSide, pos.w, pos.y + pos.h - (position.y + space_fromSide) };

			auto& tX = button->getTX();

			double scale = double(temp_pos.h) / double(pos.h);

			texture_area.x = 0;
			texture_area.y = tX.getHeight() - std::round(tX.getHeight() * scale);
			texture_area.w = tX.getWidth();
			texture_area.h = tX.getHeight() - texture_area.y;

			button->render(texture_area, temp_pos);
		}
		else if (pos.y + pos.h > position.y + position.h - space_fromSide && pos.y <= position.y + position.h - space_fromSide) {
			temp_pos = { position.x + space_fromSide, pos.y, pos.w, position.y + position.h - space_fromSide - pos.y };

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

template <>
void ScrollBar<ScrollBar_orient::VERTICAL, Render_state::COLOR>::render_buttons()
{
	static SDL_Rect temp_pos, texture_area;

	for (auto& button : buttons) {
		auto& pos = button->getPOS();

		if (pos.y >= position.y + space_fromSide && pos.y + pos.h <= position.y + position.h - space_fromSide)
			button->render();
		else if (pos.y < position.y + space_fromSide && pos.y + pos.h > position.y + space_fromSide) {
			temp_pos = { position.x + space_fromSide, position.y + space_fromSide, pos.w, pos.y + pos.h - (position.y + space_fromSide) };

			auto& tX = button->getTX();

			double scale = double(temp_pos.h) / double(pos.h);

			texture_area.x = 0;
			texture_area.y = tX.getHeight() - std::round(tX.getHeight() * scale);
			texture_area.w = tX.getWidth();
			texture_area.h = tX.getHeight() - texture_area.y;

			button->render(texture_area, temp_pos);
		}
		else if (pos.y + pos.h > position.y + position.h - space_fromSide && pos.y <= position.y + position.h - space_fromSide) {
			temp_pos = { position.x + space_fromSide, pos.y, pos.w, position.y + position.h - space_fromSide - pos.y };

			auto& tX = button->getTX();

			double scale = double(temp_pos.h) / double(pos.h);

			texture_area.x = 0;
			texture_area.y = 0;
			texture_area.w = tX.getWidth();
			texture_area.h = std::round(tX.getHeight() * scale);

			button->render(texture_area, temp_pos);
		}
	}
}*/

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::move_all(int size_x, int size_y)
{
	for (auto& button : buttons)
		button->update_about(size_x, size_y);
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::move_horizontal()
{
	static int temp_moveSize;

	switch (Mouse::getWheelState()) {
	case Mouse_wheel::UP:
		if (buttons.back()->getPOS().x + buttons.back()->getPOS().w > position.x + position.w - space_fromSide) { // sprawdz czy mo¿na jeszcze przesun¹æ
			if (buttons.back()->getPOS().x + buttons.back()->getPOS().w - Move_size > position.x + position.w - space_fromSide) {
				for (auto& button : buttons) {
					const SDL_Rect& pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x - Move_size, pos.y);
				}
			}
			else {
				const SDL_Rect& pos = buttons.back()->getPOS();
				temp_moveSize = pos.x + pos.w - (position.x + position.w - space_fromSide);

				for (auto& button : buttons) {
					const SDL_Rect& pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x - temp_moveSize, pos.y);
				}
			}
		}
		break;
	case Mouse_wheel::DOWN:
		if (buttons.front()->getPOS().x < position.x + space_fromSide) {
			if (buttons.front()->getPOS().x + Move_size < position.x + space_fromSide) {
				for (auto& button : buttons) {
					const SDL_Rect& pos = button->getPOS();
					button->update_position(pos.x + Move_size, pos.y);
				}
			}
			else {
				const SDL_Rect& pos = buttons.front()->getPOS();
				temp_moveSize = position.x + space_fromSide - pos.x;

				for (auto& button : buttons) {
					const SDL_Rect& pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x + temp_moveSize, pos.y);
				}
			}
		}
		break;
	}
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::move_vertical() // dzia³a perfekcyjnie
{
	static int temp_moveSize;

	switch (Mouse::getWheelState()) {
	case Mouse_wheel::DOWN:
		if (buttons.back()->getPOS().y + buttons.back()->getPOS().h > position.y + position.h - space_fromSide) { // sprawdz czy mo¿na jeszcze przesun¹æ
			if (buttons.back()->getPOS().y + buttons.back()->getPOS().h - Move_size > position.y + position.h - space_fromSide) {
				for (auto& button : buttons) {
					const SDL_Rect& pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x, pos.y - Move_size);
				}
			}
			else {
				const SDL_Rect& pos = buttons.back()->getPOS();
				temp_moveSize = pos.y + pos.h - (position.y + position.h - space_fromSide);

				for (auto& button : buttons) {
					const SDL_Rect& pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x, pos.y - temp_moveSize);
				}
			}
		}
		break;
	case Mouse_wheel::UP:
		if (buttons.front()->getPOS().y < position.y + space_fromSide) {
			if (buttons.front()->getPOS().y + Move_size < position.y + space_fromSide) {
				for (auto& button : buttons) {
					const SDL_Rect& pos = button->getPOS();
					button->update_position(pos.x, pos.y + Move_size);
				}
			}
			else {
				const SDL_Rect& pos = buttons.front()->getPOS();
				temp_moveSize = position.y + space_fromSide - pos.y;

				for (auto& button : buttons) {
					const SDL_Rect& pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x, pos.y + temp_moveSize);
				}
			}
		}
		break;
	}
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::events() // do poprawy - 
{
	reset_states();

	if (Mouse::is_inPOS(position))
	{
		mouse_over = true;
		if (Mouse::getWheelState() != Mouse_wheel::NONE)
		{
			switch (orient)
			{
			case ScrollBar_orient::HORIZONTAL:
				move_horizontal();
				//update_buttonRange_horizontal();
				break;
			case ScrollBar_orient::VERTICAL:
				move_vertical();
				//update_buttonRange_vertical();
				break;
			}
		}

		//buttons_rangePoint_events();

		for (auto& button : buttons) {

			button->events();
			if (button->is_mouseOver()) {
				current_mouseOver_button = button.get();
				break;
			}
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
	else
		deactivate_mouseOverEvent(); // je¿eli pozosta³ przycisk, który wymaga usuniêcia flagi mouse_Over
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::render()
{
	switch (render_state)
	{
	case Render_state::TEXTURE:
		textureBG.render(nullptr, &position);
		break;
	case Render_state::COLOR:
		Renderer::set_renderColor(colorBG);
		SDL_RenderFillRect(Renderer::get(), &position);
		Renderer::set_defaultColor();
		break;
	}

	render_buttons();
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::reset()
{
	if (current_button)
		current_button->set_active(false);
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::deactivate_buttons()
{
	if (current_button) {
		current_button->set_active(false);
		current_button = nullptr;
	}
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::deactivate_mouseOverEvent()
{
	if (current_mouseOver_button) {
		if (!current_mouseOver_button->is_active()) {
			current_mouseOver_button->mouseOver_deactivate();
			current_mouseOver_button = nullptr;
		}
	}
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::update_about(int x, int y) // przesuñ ca³y ScrollBar w³¹cznie ze wszystkimi przyciskami
{
	position.x += x; // zaktualizuj pozycjê scrollbara
	position.y += y;

	move_all(x, y); // zaktualizuj pozycjê przycisków
}

template <enum class ScrollBar_orient scroolbarOrient, enum class Render_state renderState>
void ScrollBar<scroolbarOrient, renderState>::operator=(const std::vector<BButton_ptr>& btns) // automatycznie ustala pozycje przycisków
{
	buttons = std::move(btns);

	int x = position.x + space_fromSide;
	int y = position.y + space_fromSide;

	switch (orient)
	{
	case ScrollBar_orient::HORIZONTAL:
		for (auto& button : buttons) {
			button->set_position({ x, y, button_width, button_height });
			x += button_width + button_space;
		}
		break;
	case ScrollBar_orient::VERTICAL:
		for (auto& button : buttons) {
			button->set_position({ x, y, button_width, button_height });
			y += button_height + button_space;
		}
		break;
	}
}