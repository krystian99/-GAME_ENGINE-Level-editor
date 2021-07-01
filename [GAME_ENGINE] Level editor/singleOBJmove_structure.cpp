#include "singleOBJmove_structure.h"

void singleOBJmove_structure::set(Enemy* enemy)
{
	current_enemy = enemy;

	px_left = Mouse::getX() - enemy->left();
	px_up = Mouse::getY() - enemy->up();
}

void singleOBJmove_structure::events(bool mouse_over, SDL_Rect edit_a)
{
	Rect edit_area{ edit_a };

	int tmp_px_left, tmp_px_up;

	tmp_px_left = tmp_px_up = 0;

	current_enemy->update_position(Mouse::getX() - px_left, Mouse::getY() - px_up);

	const Rect pos = Rect{ current_enemy->get_position() };

	if (mouse_over)
	{
		if (pos.up() < edit_area.up())
			tmp_px_up = edit_area.up() - current_enemy->get_position().y;

		else if (pos.down() > edit_area.down())
			tmp_px_up = edit_area.down() - pos.down();

		if (pos.left() < edit_area.left())
			tmp_px_left = edit_area.left() - pos.left();

		else if (pos.right() > edit_area.right())
			tmp_px_left = edit_area.right() - pos.right();

		current_enemy->update_position(tmp_px_left, tmp_px_up);
	}
}

void singleOBJmove_structure::events()
{
	switch (state)
	{
	case SingleOBJmove_events::SELECTING:
		break;
	case SingleOBJmove_events::MOVING_OBJ:
		break;
	case SingleOBJmove_events::SET_OBJ:
		break;
	}
}

void singleOBJmove_structure::render()
{

}
