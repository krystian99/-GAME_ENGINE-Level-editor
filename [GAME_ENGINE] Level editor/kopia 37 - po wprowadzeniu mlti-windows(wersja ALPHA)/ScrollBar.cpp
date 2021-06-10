#include "ScrollBar.h"
#include "Video_Info.h"
#include "Renderer.h"
#include "Mouse.h"

ScrollBar::ScrollBar(const SDL_Rect & pos, const std::string & texture_path, int size_expand) :
	ScrollBar{ pos, size_expand }
{
	render_state = Render_state::TEXTURE;
	textureBG.loadFromFile(texture_path);
}

ScrollBar::ScrollBar(const SDL_Rect & pos, const SDL_Color & color, int size_expand) :
	ScrollBar{ pos, size_expand }
{
	render_state = Render_state::COLOR;
	colorBG = color;
}

ScrollBar::ScrollBar(const SDL_Rect & pos, const SDL_Color & color, ScrollBar_orient ornt, int size_expand) :
	ScrollBar{ pos, color, size_expand }
{

}

ScrollBar::ScrollBar(const SDL_Rect & pos, int size_expand)
{
	position.x = std::round(pos.x * Video_Info::get_scaleW());
	position.y = std::round(pos.y * Video_Info::get_scaleH());
	position.w = std::round(pos.w * Video_Info::get_scaleW());
	position.h = std::round(pos.h * Video_Info::get_scaleH());

	if (position.w > position.h) {
		orient = ScrollBar_orient::HORIZONTAL;
		button_height = position.h - 2 * button_space;
		button_width = size_expand * Video_Info::get_scaleW();
	}
	else {
		orient = ScrollBar_orient::VERTICAL;
		button_width = position.w - 2 * button_space; // dlatego 2 razy bo przy lewej i prawej krawêdzi ma byæ taki sama pusta przestrzeñ
		button_height = size_expand * Video_Info::get_scaleH();
	}
}

void ScrollBar::render_buttons()
{
	static SDL_Rect temp_pos, texture_area;

	switch (orient) {
	case ScrollBar_orient::HORIZONTAL: // nie zosta³o ukoñczone
		for (auto & button : buttons) {
			auto & pos = button->getPOS();

			if (pos.x >= position.x + button_space && pos.x + pos.w <= position.x + position.w - button_space)
				button->render(); // renderuj ca³y przycisk
			else if (pos.x < position.x + button_space && pos.x + pos.w > position.x + button_space) {
				temp_pos = { position.x + button_space, position.y + button_space, pos.x + pos.w - (position.x + button_space) , pos.h };

				auto & tX = button->getTX();

				double scale = double(temp_pos.w) / double(pos.w);

				texture_area.x = tX.getWidth() - std::round(tX.getWidth() * scale);
				texture_area.y = 0;
				texture_area.w = tX.getWidth() - texture_area.x;
				texture_area.h = tX.getHeight();

				button->render(texture_area, temp_pos);
			}
			else if (pos.x + pos.w > position.x + position.w - button_space && pos.x <= position.x + position.w - button_space) {
				temp_pos = { pos.x, position.y + button_space, position.x + position.w - button_space - pos.x, pos.h };

				auto & tX = button->getTX();

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
		for (auto & button : buttons) {
			auto & pos = button->getPOS();

			if (pos.y >= position.y + button_space && pos.y + pos.h <= position.y + position.h - button_space)
				button->render();
			else if (pos.y < position.y + button_space && pos.y + pos.h > position.y + button_space) {
				temp_pos = { position.x + button_space, position.y + button_space, pos.w, pos.y + pos.h - (position.y + button_space) };

				auto & tX = button->getTX();

				double scale = double(temp_pos.h) / double(pos.h);

				texture_area.x = 0;
				texture_area.y = tX.getHeight() - std::round(tX.getHeight() * scale);
				texture_area.w = tX.getWidth();
				texture_area.h = tX.getHeight() - texture_area.y;

				button->render(texture_area, temp_pos);
			}
			else if (pos.y + pos.h > position.y + position.h - button_space && pos.y <= position.y + position.h - button_space) {
				temp_pos = { position.x + button_space, pos.y, pos.w, position.y + position.h -  button_space - pos.y };

				auto & tX = button->getTX();

				double scale = double(temp_pos.h) / double(pos.h);

				texture_area.x = 0;
				texture_area.y = 0;
				texture_area.w = tX.getWidth();
				texture_area.h = std::round(tX.getHeight() * scale);

				button->render(texture_area, temp_pos);
			}
		}
		break;
	}
}

void ScrollBar::move_horizontal()
{
	static int temp_moveSize;

	switch (Mouse::getWheelState()) {
	case Mouse_wheel::DOWN:
		if (buttons.back()->getPOS().x + buttons.back()->getPOS().w > position.x + position.w - button_space) { // sprawdz czy mo¿na jeszcze przesun¹æ
			if (buttons.back()->getPOS().x + buttons.back()->getPOS().w - Move_size > position.x + position.w - button_space) {
				for (auto & button : buttons) {
					const SDL_Rect & pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x - Move_size, pos.y);
				}
			}
			else {
				const SDL_Rect & pos = buttons.back()->getPOS();
				temp_moveSize = pos.x + pos.w - (position.x + position.w - button_space);

				for (auto & button : buttons) {
					const SDL_Rect & pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x - temp_moveSize, pos.y);
				}
			}
		}
		break;
	case Mouse_wheel::UP:
		if (buttons.front()->getPOS().x < position.x + button_space) {
			if (buttons.front()->getPOS().x + Move_size < position.x + button_space) {
				for (auto & button : buttons) {
					const SDL_Rect & pos = button->getPOS();
					button->update_position(pos.x + Move_size, pos.y);
				}
			}
			else {
				const SDL_Rect & pos = buttons.front()->getPOS();
				temp_moveSize = position.x + button_space - pos.x;

				for (auto & button : buttons) {
					const SDL_Rect & pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x + temp_moveSize, pos.y);
				}
			}
		}
		break;
	}
}

void ScrollBar::move_vertical() // dzia³a perfekcyjnie
{
	static int temp_moveSize;

	switch (Mouse::getWheelState()) {
	case Mouse_wheel::DOWN:
		if (buttons.back()->getPOS().y + buttons.back()->getPOS().h > position.y + position.h - button_space) { // sprawdz czy mo¿na jeszcze przesun¹æ
			if (buttons.back()->getPOS().y + buttons.back()->getPOS().h - Move_size > position.y + position.h - button_space) {
				for (auto & button : buttons) {
					const SDL_Rect & pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x, pos.y - Move_size);
				}
			}
			else {
				const SDL_Rect & pos = buttons.back()->getPOS();
				temp_moveSize = pos.y + pos.h - (position.y + position.h - button_space);

				for (auto & button : buttons) {
					const SDL_Rect & pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x, pos.y - temp_moveSize);
				}
			}
		}
		break;
	case Mouse_wheel::UP:
		if (buttons.front()->getPOS().y < position.y + button_space) {
			if (buttons.front()->getPOS().y + Move_size < position.y + button_space) {
				for (auto & button : buttons) {
					const SDL_Rect & pos = button->getPOS();
					button->update_position(pos.x, pos.y + Move_size);
				}
			}
			else {
				const SDL_Rect & pos = buttons.front()->getPOS();
				temp_moveSize = position.y + button_space - pos.y;

				for (auto & button : buttons) {
					const SDL_Rect & pos = button->getPOS(); // skrócenie identyfikatora
					button->update_position(pos.x, pos.y + temp_moveSize);
				}
			}
		}
		break;
	}
}

void ScrollBar::events()
{
	if (Mouse::getX() >= position.x && Mouse::getX() <= position.x + position.w
		&& Mouse::getY() >= position.y && Mouse::getY() <= position.y + position.h)
	{
		if (Mouse::getWheelState() != Mouse_wheel::NONE)
		{
			switch (orient) 
			{
			case ScrollBar_orient::HORIZONTAL:
				move_horizontal();
				break;
			case ScrollBar_orient::VERTICAL:
				move_vertical();
				break;
			}
		}

		for (auto & button : buttons)
			button->events();
	}
}

void ScrollBar::render()
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

void ScrollBar::operator=(const std::vector<Button*> & btns) // automatycznie ustala pozycje przycisków
{
	buttons = btns;

	int x = position.x + button_space;
	int y = position.y + button_space;

	switch (orient)
	{
	case ScrollBar_orient::HORIZONTAL:
		for (auto & button : buttons) {
			button->set_position({ x, y, button_width, button_height });
			x += button_width + button_space;
		}
		break;
	case ScrollBar_orient::VERTICAL:
		for (auto & button : buttons) {
			button->set_position({ x, y, button_width, button_height });
			y += button_height + button_space;
		}
		break;
	}
}