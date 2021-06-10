#include "Button_Menu.h"
#include "Mouse.h"

/*Button_Menu::Button_Menu(APP_state & aMain, const APP_state & st2, MENU_STATE & mMain, const MENU_STATE & st1) :
	mainState_menu{ mMain }, nextMenu_state{ st1 },
	main_state{ aMain }, nextState{ st2 }
{}*/

void Button_Menu::render_all(SDL_Renderer * rn)
{
	Button::render(rn);
	TEXT_render(rn);
}

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
	set_nextState_APP();
	mainState_menu = nextMenu_state;
}

void Button_Menu::set_nextState_APP()
{
	main_state = nextState;
}

void Button_Menu::setPOS_TEXT(const SDL_Rect * rt)
{
	textPOS = *rt;
}

void Button_Menu::events(SDL_Renderer * rn)
{
	render_all(rn);
	mouse_handler();
	moveText(-MoveSize);
}

void Button_Menu::setRenderTEXT(std::string ttf_path, std::string renderedText, int height, SDL_Color color)
{
	text.setTEXT(renderedText);
	text.loadFont(ttf_path, height, color);

	const SDL_Rect * pos = getPOS();

	textPOS = { pos->x + FRAME_SIZE, pos->y, text.getWidth(), pos->h };

	text.set_position(textPOS);
}