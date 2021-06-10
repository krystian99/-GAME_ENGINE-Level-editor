#include "Button_Menu.h"
#include "Mouse.h"

void Button_Menu::moveText(const int & size)
{
	const SDL_Rect * pos = getPOS();

	if (text.getWidth() > pos->w) {
		if (textPOS.x + textPOS.w + size > pos->x)
			textPOS.x += size;
		else
			textPOS = { pos->x + pos->w, pos->y, text.getWidth(), pos->h };

		text.set_position(textPOS);
	}
}

void Button_Menu::TEXT_render(SDL_Renderer * rn)
{
	const SDL_Rect * bt_pos = getPOS();

	if (textPOS.x >= bt_pos->x && textPOS.x + textPOS.w <= bt_pos->x + bt_pos->w)
		text.render(rn, 0, textPOS.w);
	else if (textPOS.x >= bt_pos->x && textPOS.x + textPOS.w > bt_pos->x + bt_pos->w)
	{
		SDL_Rect clip = { textPOS.x, bt_pos->y, bt_pos->x + bt_pos->w - textPOS.x, bt_pos->h };
		text.render(rn, 0, bt_pos->x + bt_pos->w - textPOS.x, &clip);
	}
	else if (textPOS.x < bt_pos->x && textPOS.x + textPOS.w > bt_pos->x + bt_pos->w) {
		int start_pos = bt_pos->x - textPOS.x;
		text.render(rn, start_pos, bt_pos->w, getPOS());
	}
	else if (textPOS.x < bt_pos->x && textPOS.x + textPOS.w < bt_pos->x + bt_pos->w) {
		SDL_Rect clip = { bt_pos->x, bt_pos->y, textPOS.x + textPOS.w - bt_pos->x, bt_pos->h };
		int start_pos = bt_pos->x - textPOS.x;
		int w = textPOS.x + textPOS.w - bt_pos->x;
		text.render(rn, start_pos, w, &clip);
	}

}

void Button_Menu::onClick()
{
	Button::onClick();

	set_nextState_APP();
	mainState_menu = nextMenu_state;
}

void Button_Menu::onMouseOver()
{

}

void Button_Menu::set_nextState_APP()
{
	main_state = nextState;
}

void Button_Menu::events()
{
	mouse_handler();
}

void Button_Menu::events_independent()
{
	moveText(-MoveSize);
}

void Button_Menu::render(SDL_Renderer * rn)
{
	Button::render(rn);
	TEXT_render(rn);
}