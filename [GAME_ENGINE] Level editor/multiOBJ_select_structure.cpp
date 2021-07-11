#include "multiOBJ_select_structure.h"
#include "Renderer.h"
#include "CoordinateBar_map.h"

multiOBJ_select_structure::multiOBJ_select_structure(Enemies& en, const Rect* edit_a, const Rect* mapBG_a)
	: enemies{ en }
{
	edit_area = edit_a;
	mapBG_area = mapBG_a;
}

void multiOBJ_select_structure::events()
{
	Object::events();

	selected_area.events();

	switch (state)
	{
	case States::MOVING_OBJs:
		events_moving();
		break;
	case States::SET_OBJs:
		movingFinsh_event();
		break;
	}
}

void multiOBJ_select_structure::set_borderOBJ(const Rect& pos, Enemy* enemy)
{
	if (enemy_left)
	{
		if (pos.left() < enemy_left->left())
			enemy_left = enemy;
	}
	else
		enemy_left = enemy;

	if (enemy_right)
	{
		if (pos.right() > enemy_right->right())
			enemy_right = enemy;
	}
	else
		enemy_right = enemy;

	if (enemy_up)
	{
		if (pos.up() < enemy_up->up())
			enemy_up = enemy;
	}
	else
		enemy_up = enemy;

	if (enemy_down)
	{
		if (pos.down() > enemy_down->down())
			enemy_down = enemy;
	}
	else
		enemy_down = enemy;

	moving_objects.push_back({ enemy });
}

void multiOBJ_select_structure::selectingOBJs()
{
	const int& mX = Mouse::getX();
	const int& mY = Mouse::getY();

	auto& point = clicked_point.get();
	auto& map_point = clicked_pointMap.get();

	int x, y, w, h;

	int mapX, mapY, mapH, mapW;

	if (mX < point.x)
	{
		x = mX;
		mapX = CoordinateBar_map::getX();

		w = point.x - mX;
		mapW = map_point.x - CoordinateBar_map::getX();
	}
	else {
		x = point.x;
		mapX = map_point.x;

		w = mX - point.x;
		mapW = CoordinateBar_map::getX() - map_point.x;
	}
	if (mY < point.y) {
		y = mY;
		mapY = CoordinateBar_map::getY();

		h = point.y - mY;
		mapH = map_point.y - CoordinateBar_map::getY();
	}
	else {
		y = point.y;
		mapY = map_point.y;

		h = mY - point.y;
		mapH = CoordinateBar_map::getY() - map_point.y;
	}

	int RenderPOS_X, RenderPOS_Y;
	double scaleX, scaleY;

	scaleX = double(selected_area.get_mapX() - mapBG_area->left()) / double(mapBG_area->getW());
	scaleY = double(selected_area.get_mapY() - mapBG_area->up()) / double(mapBG_area->getH());

	RenderPOS_X = round(scaleX * edit_area->getW()) + edit_area->left();
	RenderPOS_Y = round(scaleY * edit_area->getH()) + edit_area->up();

	selected_area.set_mapPOS(mapX, mapY, mapW, mapH);
	selected_area.set_position(RenderPOS_X, RenderPOS_Y, w, h);
}

void multiOBJ_select_structure::on_mouseL1hit()
{
	switch (state)
	{
	case States::SELECTING_OBJs:
		reset();

		clicked_point = Mouse::get_clickedPoint();
		clicked_pointMap = { CoordinateBar_map::getX(), CoordinateBar_map::getY() };
		break;
	}
}

void multiOBJ_select_structure::on_mouseR1hit()
{
	switch (state)
	{
	case States::SELECTING_OBJs:
		clicked_point = Mouse::get_clickedPoint();
		clicked_pointMap = { CoordinateBar_map::getX(), CoordinateBar_map::getY() };
		updateOBJs();

		if (selected_area.is_mouseKey_1hit(Mouse_key::R_BUTTON))
			setState(States::MOVING_OBJs);
		break;
	case States::MOVING_OBJs:
		setState(States::SET_OBJs);
		break;
	}
}

void multiOBJ_select_structure::on_mouseL_press()
{
	switch (state)
	{
	case States::SELECTING_OBJs:
		selectingOBJs();
		break;
	}
}

void multiOBJ_select_structure::on_mouseL_pressUP()
{
	switch (state)
	{
	case States::SELECTING_OBJs:
		OBJs_set();
		break;
	}
}


void multiOBJ_select_structure::on_mouseWheel_up_1hit()
{
	moveMap_Event();
}

void multiOBJ_select_structure::on_mouseWheel_down_1hit()
{
	moveMap_Event();
}

void multiOBJ_select_structure::on_keyboardKey_DELETE_1hit()
{
	reset();

	for (int i = 0; i < enemies.size(); i++) {
		auto& enemy = enemies[i];

		if (enemy->is_selected()) {
			std::swap(enemy, enemies.back());
			enemies.pop_back();
			i--;
		}
	}
}

void multiOBJ_select_structure::render()
{
	SDL_Rect tmp = selected_area.get_position();

	Renderer::set_renderColor({ 0, 0, 255, 255 });

	bool RENDER = true;
	
	if (selected_area.left() < edit_area->left()) {
		tmp.x = edit_area->left();

		tmp.w -= edit_area->left() - selected_area.left();

		if (tmp.w < 0)
			RENDER = false;
	}
	if (selected_area.up() < edit_area->up()) {
		tmp.y = edit_area->up();
		tmp.h -= edit_area->up() - selected_area.up();
	}
	if (selected_area.right() > edit_area->right()) {
		tmp.w = edit_area->right() - selected_area.left();

		if (tmp.x >= edit_area->right())
			RENDER = false;
	}
	if (selected_area.down() > edit_area->down())
		tmp.h = edit_area->down() - selected_area.up();

	if (RENDER)
		SDL_RenderDrawRect(Renderer::get(), &tmp);
	Renderer::set_defaultColor();
}

void multiOBJ_select_structure::OBJs_set()
{
	for (auto& enemy : enemies) {
		auto& pos_temp = enemy->get_position();

		Rect pos;
		pos.set_position(pos_temp);

		if (pos.left() > selected_area.left() && pos.up() > selected_area.up()
			&& pos.right() < selected_area.right() && pos.down() < selected_area.down())
		{
			set_borderOBJ(pos, enemy.get()); // ustaw obiekt graniczny i dodaj do obiektow przesuwanych
			enemy->set_selectState(true);
		}
		else
			enemy->set_selectState(false);
	}

	if (moving_objects.size() == 0)
		reset();
}

void multiOBJ_select_structure::movingFinsh_event()
{
	setState(States::SELECTING_OBJs);

	for (auto& moveOBJ : moving_objects) {
		int RenderPOS_X, RenderPOS_Y;
		double scaleTX_w, scaleTX_h;
		int x, y;

		double scaleX, scaleY;

		scaleTX_w = double(moveOBJ.enemy->left() - edit_area->left()) / edit_area->getW();
		scaleTX_h = double(moveOBJ.enemy->up() - edit_area->up()) / edit_area->getH();

		x = mapBG_area->left() + round(mapBG_area->getW() * scaleTX_w);
		y = mapBG_area->up() + round(mapBG_area->getH() * scaleTX_h);

		scaleX = double(x - mapBG_area->left()) / double(mapBG_area->getW());
		scaleY = double(y - mapBG_area->up()) / double(mapBG_area->getH());
		RenderPOS_X = round(scaleX * edit_area->getW()) + edit_area->left();
		RenderPOS_Y = round(scaleY * edit_area->getH()) + edit_area->up();

		moveOBJ.setPOS(RenderPOS_X, RenderPOS_Y, x, y);
	}

	int RenderPOS_X, RenderPOS_Y;
	int x, y; // dla mapy
	double scale_renderX, scale_renderY;
	double scale_mapX, scale_mapY;

	scale_mapX = double(selected_area.left() - edit_area->left()) / edit_area->getW();
	scale_mapY = double(selected_area.up() - edit_area->up()) / edit_area->getH();

	x = mapBG_area->left() + round(mapBG_area->getW() * scale_mapX);
	y = mapBG_area->up() + round(mapBG_area->getH() * scale_mapY);

	scale_renderX = double(x - mapBG_area->left()) / double(mapBG_area->getW());
	scale_renderY = double(y - mapBG_area->up()) / double(mapBG_area->getH());

	RenderPOS_X = round(scale_renderX * edit_area->getW()) + edit_area->left();
	RenderPOS_Y = round(scale_renderY * edit_area->getH()) + edit_area->up();

	selected_area.set_position(RenderPOS_X, RenderPOS_Y);
	selected_area.set_mapPOS(x, y);
}

void multiOBJ_select_structure::events_moving()
{
	if (is_mouseOver()) {
		int tmp_px_left, tmp_px_up, tmp_px_left_map, tmp_px_up_map;

		selected_area.setX(Mouse::getX() - px_left);
		selected_area.setY(Mouse::getY() - px_up);

		tmp_px_left = tmp_px_up = 0;
		tmp_px_left_map = tmp_px_up_map = 0;

		for (auto& enemy : moving_objects)
			enemy.setPOS(Mouse::getX() - enemy.px_left, Mouse::getY() - enemy.px_up, CoordinateBar_map::getX() - enemy.map_pxLEFT, CoordinateBar_map::getY() - enemy.map_pxUP);

		if (enemy_up->up() < edit_area->up())
			tmp_px_up = edit_area->up() - enemy_up->up();

		else if (enemy_down->down() > edit_area->down())
			tmp_px_up = edit_area->down() - enemy_down->down();

		if (enemy_left->left_map() < mapBG_area->left())
			tmp_px_left = mapBG_area->left() - enemy_left->left_map();

		else if (enemy_right->right_map() > mapBG_area->right())
			tmp_px_left = mapBG_area->right() - enemy_right->right_map();

		if (enemy_up->up_map() < mapBG_area->up())
			tmp_px_up_map = mapBG_area->up() - enemy_up->up_map();

		else if (enemy_down->down_map() > mapBG_area->down())
			tmp_px_up_map = mapBG_area->down() - enemy_down->down_map();

		if (enemy_left->left_map() < mapBG_area->left())
			tmp_px_left_map = mapBG_area->left() - enemy_left->left_map();

		else if (enemy_right->right_map() > mapBG_area->right())
			tmp_px_left_map = mapBG_area->right() - enemy_right->right_map();

		selected_area.updateX(tmp_px_left);
		selected_area.updateY(tmp_px_up);

		for (auto& moveOBJ : moving_objects)
			moveOBJ.updatePOS(tmp_px_left, tmp_px_up, tmp_px_left_map, tmp_px_up_map);
	}
}

void multiOBJ_select_structure::moveMap_Event()
{
	double scaleX, scaleY;

	int RenderPOS_X, RenderPOS_Y;

	scaleX = double(selected_area.get_mapX() - mapBG_area->left()) / double(mapBG_area->getW());
	scaleY = double(selected_area.get_mapY() - mapBG_area->up()) / double(mapBG_area->getH());

	RenderPOS_X = round(scaleX * edit_area->getW()) + edit_area->left();
	RenderPOS_Y = round(scaleY * edit_area->getH()) + edit_area->up();

	selected_area.set_position(RenderPOS_X, RenderPOS_Y);
}

void multiOBJ_select_structure::reset()
{
	setState(States::SELECTING_OBJs);

	enemy_up = enemy_down = enemy_left = enemy_right = nullptr;
	moving_objects.clear();
	selected_area.set_position(0, 0, 1, 1);
}

void multiOBJ_select_structure::updateOBJs()
{
	// zachowanie proporcji po kliknieciu
	auto& clck_point = clicked_point.get();

	px_up = clck_point.y - selected_area.up(); // ile px w gore potrzeba by zaznaczenie bylo w oryginalnej pozycji
	px_left = clck_point.x - selected_area.left();

	for (auto& enemy : moving_objects)
	{
		enemy.px_left = clck_point.x - enemy.enemy->left();
		enemy.px_up = clck_point.y - enemy.enemy->up();

		enemy.map_pxLEFT = clicked_pointMap.getX() - enemy.enemy->left_map();
		enemy.map_pxUP = clicked_pointMap.getY() - enemy.enemy->up_map();
	}
}

void multiOBJ_select_structure::Move_OBJ::updatePOS(int upd_renderX, int upd_renderY, int upd_mapX, int upd_mapY)
{
	enemy->update_position(upd_renderX, upd_renderY);
	enemy->update_mapPOS(upd_mapX, upd_mapY);
}

void multiOBJ_select_structure::Move_OBJ::setPOS(int renderX, int renderY, int mapX, int mapY)
{
	enemy->set_position(renderX, renderY);
	enemy->set_mapPOS(mapX, mapY);
}
