#include "singleOBJmove_structure.h"
#include "Mouse.h"
#include "CoordinateBar_map.h"

SingleOBJmove_events singleOBJmove_structure::state{ SingleOBJmove_events::SELECTING };

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

void singleOBJmove_structure::render()
{

}

void singleOBJmove_structure::movingOBJ_events()
{
	double scaleTX_w, scaleTX_h;
	int x, y;

	scaleTX_w = double(Mouse::getX() - px_left - edit_area.left()) / edit_area.getW();
	scaleTX_h = double(Mouse::getY() - px_up - edit_area.up()) / edit_area.getH();

	x = mapBG_area.left() + round(mapBG_area.getW() * scaleTX_w);
	y = mapBG_area.up() + round(mapBG_area.getH() * scaleTX_h);

	int RenderPOS_X, RenderPOS_Y;
	double scaleX, scaleY;

	scaleX = double(x - mapBG_area.left()) / double(mapBG_area.getW());
	scaleY = double(y - mapBG_area.up()) / double(mapBG_area.getH());

	RenderPOS_X = round(scaleX * edit_area.getW()) + edit_area.left();
	RenderPOS_Y = round(scaleY * edit_area.getH()) + edit_area.up();

	current_enemy->set_mapPOS(x, y);
	current_enemy->set_position(RenderPOS_X, RenderPOS_Y);

	mouseR_event();

	/*int tmp_px_left, tmp_px_up;

	tmp_px_left = tmp_px_up = 0;

	current_enemy->set_position(Mouse::getX() - px_left, Mouse::getY() - px_up);
	current_enemy->set_mapPOS(CoordinateBar_map::getX(), CoordinateBar_map::getY());*/

	if (Mouse::is_pressedL_once())
		setState(SingleOBJmove_events::SET_OBJ);

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
		if (enemy->is_clicked()) {
			if (!enemy->is_selected())
			{
				enemy->switch_selected_state();

				set(enemy.get());

				state = SingleOBJmove_events::MOVING_OBJ;
			}
			else
				enemy->switch_selected_state();
			break;
		}
	}
}

void singleOBJmove_structure::setOBJ_onMap()
{
	if (Mouse::is_pressedL_once())
	{
		double scaleTX_w, scaleTX_h;
		int x, y;

		scaleTX_w = double(current_enemy->left() - edit_area.left()) / edit_area.getW();
		scaleTX_h = double(current_enemy->up() - edit_area.up()) / edit_area.getH();

		x = mapBG_area.left() + round(mapBG_area.getW() * scaleTX_w);
		y = mapBG_area.up() + round(mapBG_area.getH() * scaleTX_h);

		int RenderPOS_X, RenderPOS_Y;
		double scaleX, scaleY;
		scaleX = double(x - mapBG_area.left()) / double(mapBG_area.getW());
		scaleY = double(y - mapBG_area.up()) / double(mapBG_area.getH());
		RenderPOS_X = round(scaleX * edit_area.getW()) + edit_area.left();
		RenderPOS_Y = round(scaleY * edit_area.getH()) + edit_area.up();

		current_enemy->set_mapPOS(x, y);
		current_enemy->set_position(RenderPOS_X, RenderPOS_Y);

		reset();

		setState(SingleOBJmove_events::SELECTING);
	}
}

void singleOBJmove_structure::mouseR_event()
{
	if (Mouse::is_inState(Mouse_key::R_BUTTON))
		current_enemy->switch_orient();
}

void singleOBJmove_structure::mouse_handler()
{
}
