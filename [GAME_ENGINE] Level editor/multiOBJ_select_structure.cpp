#include "multiOBJ_select_structure.h"
#include "Renderer.h"
#include "CoordinateBar_map.h"

multiOBJ_select_structure::multiOBJ_select_structure(Enemies& en, const Map_mouseHandler& map_mouse, const Rect* edit_a, const Rect* mapBG_a)
	: enemies{ en }, map_mouseHandler{ map_mouse }
{
	edit_area = edit_a;
	mapBG_area = mapBG_a;
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

void multiOBJ_select_structure::render()
{
	SDL_Rect tmp = get_position();

	Renderer::set_renderColor({ 0, 0, 255, 255 });

	bool RENDER = true;

	if (left() < edit_area->left()) {
		tmp.x = edit_area->left();

		tmp.w -= edit_area->left() - left();

		if (tmp.w < 0)
			RENDER = false;
	}
	if (up() < edit_area->up()) {
		tmp.y = edit_area->up();
		tmp.h -= edit_area->up() - up();
	}
	if (right() > edit_area->right()) {
		tmp.w = edit_area->right() - left();

		if (tmp.x >= edit_area->right())
			RENDER = false;
	}
	if (down() > edit_area->down())
		tmp.h = edit_area->down() - up();

	if (RENDER)
		SDL_RenderDrawRect(Renderer::get(), &tmp);
	Renderer::set_defaultColor();
}

// uruchamiane 
void multiOBJ_select_structure::OBJs_set(Enemies& enemies, const Rect& edit_area)
{
	for (auto& enemy : enemies) {
		auto& pos_temp = enemy->get_position();

		Rect pos;
		pos.set_position(pos_temp);

		if (pos.left() > left() && pos.up() > up()
			&& pos.right() < right() && pos.down() < down())
		{
			set_borderOBJ(pos, enemy.get()); // ustaw obiekt graniczny i dodaj do obiektow przesuwanych
			enemy->set_selectState(true);
		}
		else
			enemy->set_selectState(false);
	}

	if (moving_objects.size() == 0)
		reset(edit_area.get_position());
}

void multiOBJ_select_structure::events()
{
	if (Keyboard::is_pressedKey(Key::DELETE)) {
		reset(edit_area->get_position());
		for (int i = 0; i != enemies.size(); i++) {
			if (enemies[i]->is_selected()) {
				std::swap(enemies[i], enemies.back());
				enemies.pop_back();
				i--;
			}
		}
	}
}

void multiOBJ_select_structure::mouse_events()
{
	const int& mX = Mouse::getX();
	const int& mY = Mouse::getY();

	auto& point = Mouse::get_clickedPoint();
	auto& map_point = map_mouseHandler.get_clickedPoint();

	if (Mouse::isUpdated()) {
		int x, y, w, h;

		int mapX, mapY, mapH, mapW;

		if (mX < point.x)
		{
			x = mX;
			mapX = CoordinateBar_map::getX();

			w = point.x - mX;
			mapW = map_point.getX() - CoordinateBar_map::getX();
		}
		else {
			x = point.x;
			mapX = map_point.getX();

			w = mX - point.x;
			mapW = CoordinateBar_map::getX() - map_point.getX();
		}
		if (mY < point.y) {
			y = mY;
			mapY = CoordinateBar_map::getY();

			h = point.y - mY;
			mapH = map_point.getY() - CoordinateBar_map::getY();
		}
		else {
			y = point.y;
			mapY = map_point.getY();

			h = mY - point.y;
			mapH = CoordinateBar_map::getY() - map_point.getY();
		}

		set_mapPos(mapX, mapY, mapW, mapH);

		int RenderPOS_X, RenderPOS_Y;
		double scaleX, scaleY;

		scaleX = double(get_mapX() - mapBG_area->left()) / double(mapBG_area->getW());
		scaleY = double(get_mapY() - mapBG_area->up()) / double(mapBG_area->getH());

		RenderPOS_X = round(scaleX * edit_area->getW()) + edit_area->left();
		RenderPOS_Y = round(scaleY * edit_area->getH()) + edit_area->up();

		set_position(RenderPOS_X, RenderPOS_Y, w, h);
	}
}

void multiOBJ_select_structure::moveEvent_mouseR()
{
	setState_movingOBJs(false);

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

		moveOBJ.enemy->set_mapPOS(x, y);
		moveOBJ.enemy->set_position(RenderPOS_X, RenderPOS_Y);
	}

	int RenderPOS_X, RenderPOS_Y;
	int x, y; // dla mapy
	double scale_renderX, scale_renderY;
	double scale_mapX, scale_mapY;

	scale_mapX = double(left() - edit_area->left()) / edit_area->getW();
	scale_mapY = double(up() - edit_area->up()) / edit_area->getH();

	x = mapBG_area->left() + round(mapBG_area->getW() * scale_mapX);
	y = mapBG_area->up() + round(mapBG_area->getH() * scale_mapY);

	scale_renderX = double(x - mapBG_area->left()) / double(mapBG_area->getW());
	scale_renderY = double(y - mapBG_area->up()) / double(mapBG_area->getH());

	RenderPOS_X = round(scale_renderX * edit_area->getW()) + edit_area->left();
	RenderPOS_Y = round(scale_renderY * edit_area->getH()) + edit_area->up();

	mapPos.set_position(x, y);
	set_position(RenderPOS_X, RenderPOS_Y);
}

void multiOBJ_select_structure::events_moving(bool mouse_over, const SDL_Rect& edit_a)
{
	setState_movingOBJs(true);

	Rect edit_area{ edit_a };

	int tmp_px_left, tmp_px_up;

	setX(Mouse::getX() - px_left);
	setY(Mouse::getY() - px_up);

	tmp_px_left = tmp_px_up = 0;

	// nie wiem o co kaman ale cos zmienia pozycje renderowania i musi byæ najpierw ta pêtla
	for (auto& enemy : moving_objects)
		enemy.enemy->set_position(Mouse::getX() - enemy.px_left, Mouse::getY() - enemy.px_up);

	if (mouse_over) {

		if (enemy_up->up() < edit_area.up())
			tmp_px_up = edit_area.up() - enemy_up->up();

		else if (enemy_down->down() > edit_area.down())
			tmp_px_up = edit_area.down() - enemy_down->down();

		if (enemy_left->left() < edit_area.left())
			tmp_px_left = edit_area.left() - enemy_left->left();

		else if (enemy_right->right() > edit_area.right())
			tmp_px_left = edit_area.right() - enemy_right->right();

		updateX(tmp_px_left);
		updateY(tmp_px_up);

		for (auto& moveOBJ : moving_objects)
			moveOBJ.enemy->update_position(tmp_px_left, tmp_px_up);
	}
}
void multiOBJ_select_structure::moveMap_Event()
{
	double scaleX, scaleY;

	int RenderPOS_X, RenderPOS_Y;

	scaleX = double(get_mapX() - mapBG_area->left()) / double(mapBG_area->getW());
	scaleY = double(get_mapY() - mapBG_area->up()) / double(mapBG_area->getH());

	RenderPOS_X = round(scaleX * edit_area->getW()) + edit_area->left();
	RenderPOS_Y = round(scaleY * edit_area->getH()) + edit_area->up();

	update_renderPOS(RenderPOS_X, RenderPOS_Y);
}
void multiOBJ_select_structure::update_renderPOS(int x, int y)
{
	setX(x);
	setY(y);
}

void multiOBJ_select_structure::set_mapPos(Rect&& area)
{
	mapPos = std::move(area);
}

void multiOBJ_select_structure::set_mapPOS(int x, int y)
{
	mapPos.set_position(x, y);
}

void multiOBJ_select_structure::set_mapPos(int x, int y, int w, int h)
{
	mapPos.set_position(x, y, w, h);
}

void multiOBJ_select_structure::reset(SDL_Rect a)
{
	enemy_up = enemy_down = enemy_left = enemy_right = nullptr;
	moving_objects.clear();
	set_position(a.x, a.y, 1, 1);
}

void multiOBJ_select_structure::updateOBJs(SDL_Point clicked_point)
{
	// zachowanie proporcji po kliknieciu
	px_up = clicked_point.y - up(); // ile px w gore potrzeba by zaznaczenie bylo w oryginalnej pozycji
	px_left = clicked_point.x - left();

	for (auto& enemy : moving_objects)
	{
		enemy.px_left = clicked_point.x - enemy.enemy->get_position().x;
		enemy.px_up = clicked_point.y - enemy.enemy->get_position().y;
	}
}

void multiOBJ_select_structure::setState_movingOBJs(bool state)
{
	is_movingOBJs = state;
}
