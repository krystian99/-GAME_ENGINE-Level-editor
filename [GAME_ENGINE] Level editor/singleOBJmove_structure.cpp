#include "singleOBJmove_structure.h"
#include "Mouse.h"

singleOBJmove_structure::SingleOBJmove_events singleOBJmove_structure::state{ SingleOBJmove_events::SELECTING };

void singleOBJmove_structure::set(Enemy* enemy)
{
	current_enemy = enemy;

	px_left = Mouse::getX() - enemy->left();
	px_up = Mouse::getY() - enemy->up();
}

void singleOBJmove_structure::setState(SingleOBJmove_events st)
{
	state = st;
}

void singleOBJmove_structure::events()
{
	Object::events();

	switch (state)
	{
	case SingleOBJmove_events::SELECTING:
		selectingObject_events();
		break;
	case SingleOBJmove_events::MOVING_OBJ:
		movingOBJ_events();
		break;
	case SingleOBJmove_events::SET_OBJ:
		setOBJ_onMap();
		break;
	}
}

void singleOBJmove_structure::movingOBJ_events()
{
	current_enemy->set_mapPOS(Mouse::getX() - px_left, Mouse::getY() - px_up, edit_area, mapBG_area);

	int tmp_px_left, tmp_px_up;

	tmp_px_left = tmp_px_up = 0;

	const Rect pos = Rect{ current_enemy->get_position() };

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

void singleOBJmove_structure::selectingObject_events()
{
	for (auto& enemy : enemies) {
		if (enemy->is_mouseKey_1hit(Mouse_key::L_BUTTON)) {
			set(enemy.get());

			state = SingleOBJmove_events::MOVING_OBJ;
			break;
		}
	}
}

void singleOBJmove_structure::setOBJ_onMap()
{
	//current_enemy->set_mapPOS(edit_area, mapBG_area);

	reset();

	setState(SingleOBJmove_events::SELECTING);
}

void singleOBJmove_structure::on_mouseL1hit()
{
	switch (state)
	{
	case SingleOBJmove_events::MOVING_OBJ:
		setState(SingleOBJmove_events::SET_OBJ);
		break;
	}
}

void singleOBJmove_structure::on_mouseR1hit()
{
	switch (state) {
	case SingleOBJmove_events::MOVING_OBJ:
		current_enemy->switch_orient();
		break;
	}
}
