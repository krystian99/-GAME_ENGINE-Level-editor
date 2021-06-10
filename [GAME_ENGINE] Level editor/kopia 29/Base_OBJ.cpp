#include "Base_OBJ.h"
#include "Mouse.h"

void Base_OBJ::events()
{
	mouse_handler();
}

void Base_OBJ::set_position(const int & render_X, const int & render_Y)
{
	render_position.x = render_X;
	render_position.y = render_Y;
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