#include "Base_OBJ.h"
#include "Mouse.h"

double Base_OBJ::SIZE_MULTIPLIER{ 1 };

void Base_OBJ::events()
{
	mouse_handler();
}

void Base_OBJ::set_selectState(bool st)
{
	selected = st;
}

void Base_OBJ::switch_selected_state()
{
	selected = !selected;
}

bool Base_OBJ::set_size_multiplier(double size)
{
	if (size == 0) 
		return false;
	SIZE_MULTIPLIER = size;
	return true;
}

bool Base_OBJ::update_multiplierUP()
{
	SIZE_MULTIPLIER += MULTIPLIER_ADD;
	return true;
}

bool Base_OBJ::update_multiplierDOWN()
{
	if (SIZE_MULTIPLIER - MULTIPLIER_ADD < 0)
		return false;
	SIZE_MULTIPLIER -= MULTIPLIER_ADD;
	return true;
}

void Base_OBJ::update_renderPOS(const int & render_X, const int & render_Y)
{
	render_position.x = render_X;
	render_position.y = render_Y;
}

void Base_OBJ::set_renderPOS(const int & x, const int & y, const int & w, const int & h)
{
	render_position = { x, y, w, h };
}

void Base_OBJ::mouse_handler()
{
	clicked = false;
	mouse_over = false;

	if (Mouse::getX() >= render_position.x && Mouse::getX() <= render_position.x + render_position.w
		&& Mouse::getY() >= render_position.y && Mouse::getY() <= render_position.y + render_position.h)
	{
		mouse_over = true;
		onMouseOver(); // gdy myszka jest na pozycji przycisku
		if (Mouse::getBt_state() == Mouse_key::L_BUTTON) {
			l_bt_pressing = true;
		}
		else if (Mouse::getBt_state() != Mouse_key::L_BUTTON && l_bt_pressing) {
			clicked = true;
			onClick();
			l_bt_pressing = false;
		}
	}
}