#include "EDIT_AREA_LC.h"
#include "Mouse.h"
#include <cmath>

Texture OBJ_TEST::TX{};

static const std::string levels_save_path = "data/levels/saves/";

void EDIT_AREA_LC::Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	setPOS(dm, scaleW, scaleH); // ustala pozycjê
	test_objectTX.loadFromFile("data/textures/test.png");
	OBJ_TEST::setTexture("data/textures/test.png");
}

void EDIT_AREA_LC::load_MAP(const std::string & bg)
{
	mapBG.loadFromFile(bg);
	setMap_renderArea();
}

void EDIT_AREA_LC::saveLevel()
{
	using std::ios_base;

	save.open((levels_save_path + level_name).c_str(), ios_base::out | ios_base::binary);

	if (save.is_open()) {
		for (auto & enemy : objects_test)
			save.write(reinterpret_cast<const char*>(&enemy.getData()), sizeof(enemy.getData()));
	}
	save.close();
}

bool EDIT_AREA_LC::loadLevel_test(const std::string & level)
{
	static bool good;
	good = false;
	using std::ios_base;
	clearALL();

	level_name = level;
	load.open((levels_save_path + level).c_str(), ios_base::in | ios_base::binary);

	if (load.is_open()) {
		while (load.read(reinterpret_cast<char*>(&data_object_test), sizeof(data_object_test)))
			createOBJ(data_object_test.x, data_object_test.y);
		good = true;
	}
	load.close();
	return good;
}

void EDIT_AREA_LC::createLevel_test(const std::string & l_name)
{
	level_name = l_name;
}

void EDIT_AREA_LC::clearALL()
{
	objects_test.clear();
}

void EDIT_AREA_LC::events(SDL_Renderer * rn)
{
	mouse_handler();

	events_enemies();

	switch (edit_state)
	{
	case EditArea_LC_state::SELECTING_OBJ:
		selecingObjects_events();
		break;
	case EditArea_LC_state::MOVING_OBJ:
		movingOBJ_events(rn);
		break;
	case EditArea_LC_state::MOVING_MAP:
		movingMap_events();
		break;
	case EditArea_LC_state::PLACING_OBJ:
		placingObjects_events(rn);
		break;
	case EditArea_LC_state::DELETING_OBJ:
		deletingObjects_events();
		break;
	}
}

void EDIT_AREA_LC::mouse_handler()
{
	static int mX, mY;
	mX = Mouse::getMousePOSx();
	mY = Mouse::getMousePOSy();

	if (mX >= position.x && mX <= position.x + position.w
		&& mY >= position.y && mY <= position.y + position.h)
	{
		if (Mouse::getLState()) {
			if (edit_state == EditArea_LC_state::MOVING_MAP)
				setMap_view();
		}
		if (Mouse::getButtonState() == Mouse_key::L_BUTTON)
		{
			if (edit_state == EditArea_LC_state::MOVING_MAP) {
				moving_map = true;
			}
			//on_buttonL_MousePress(mX, mY);
			if (!lBT_clicked) {
				lBT_clicked = true;
				on_buttonL_MouseClick(mX, mY);
			}
		}
		else if (Mouse::getButtonState() == Mouse_key::NONE && lBT_clicked) {
			lBT_clicked = false;
			if (edit_state == EditArea_LC_state::MOVING_MAP)
				moving_map = false;
		}
	}
}

void EDIT_AREA_LC::setPOS(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	int x = round(20 * scaleW);
	int y = round(80 * scaleH);
	int w = dm->w - round(130 * scaleW) - x;
	int h = dm->h - round(80 * scaleH) - y;

	position = { x, y, w, h };
}

void EDIT_AREA_LC::setMap_renderArea()
{
	SDL_Rect map;
	double scale = double(mapBG.getHeight()) / double(position.h);
	map_renderArea.setScale(scale);
	map.x = 0;
	map.y = 0;
	map.h = mapBG.getHeight();
	map.w = round(mapBG.getWidth() * scale);


	map_renderArea.Init(map);
}

void EDIT_AREA_LC::setMap_view()
{
	static double scaleX, scale_recentX;
	static double scaleY, scale_recentY;

	static int pointX, point_recentX;

	static int maprender_absX, maprender_absY;

	if (Mouse::getMousePOSx() < Mouse::getRecent_x() || Mouse::getMousePOSx() > Mouse::getRecent_x()
		|| Mouse::getMousePOSy() < Mouse::getRecent_y() || Mouse::getMousePOSy() > Mouse::getRecent_y()) 
	{
		scaleX = double(Mouse::getMousePOSx() - position.x) / double(position.w);
		scale_recentX = double(Mouse::getRecent_x() - position.x) / double(position.w);

		pointX = map_renderArea.area.x + round(map_renderArea.area.w * scaleX);
		point_recentX = map_renderArea.area.x + round(map_renderArea.area.w * scale_recentX);

		maprender_absX = abs(pointX - point_recentX);

		if (Mouse::getMousePOSx() < Mouse::getRecent_x() && map_renderArea.canMove_r()) {
			if (map_renderArea.area.x + maprender_absX + map_renderArea.area.w < mapBG.getWidth())
				map_renderArea.area.x += maprender_absX;
			else
				map_renderArea.area.x = mapBG.getWidth() - map_renderArea.area.w;
		}
		else if (Mouse::getMousePOSx() > Mouse::getRecent_x() && map_renderArea.canMove_l()) {

			if (map_renderArea.area.x - maprender_absX > 0) 
				map_renderArea.area.x -= maprender_absX;
			else
				map_renderArea.area.x = 0;
		}

		for (auto & enemy : objects_test) {
			static int RenderPOS_X, RenderPOS_Y;

			scaleX = double(enemy.getX() - map_renderArea.getPOS().x) / double(map_renderArea.getPOS().w);
			scaleY = double(enemy.getY() - map_renderArea.getPOS().y) / double(map_renderArea.getPOS().h);

			RenderPOS_X = round(scaleX * position.w) + position.x;
			RenderPOS_Y = round(scaleY * position.h) + position.y;

			enemy.setRenderPos(RenderPOS_X, RenderPOS_Y);
		}
	}
}

void EDIT_AREA_LC::renderBackground(SDL_Renderer * rn)
{
	mapBG.render(rn, &map_renderArea.getPOS(), &position);
}

void EDIT_AREA_LC::render(SDL_Renderer * rn)
{
	renderBackground(rn);
	renderEnemies(rn);
	renderBlocks(rn);

	SDL_SetRenderDrawColor(rn, 255, 0, 0, 255);
	SDL_RenderDrawRect(rn, &position);
	SDL_SetRenderDrawColor(rn, 255, 255, 255, 255);

	render_eventsDependent(rn); // aktualizuje stan zdarzen i renderuje - tzw. renderowanie zale¿ne od zdzarzeñ
}

void EDIT_AREA_LC::render_eventsDependent(SDL_Renderer * rn)
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	if (edit_state == EditArea_LC_state::PLACING_OBJ) {
		mouse_updateDraw = { mX, mY, OBJ_TEST::w, OBJ_TEST::h };
		test_objectTX.render(rn, nullptr, &mouse_updateDraw);
	}
	else if (edit_state == EditArea_LC_state::MOVING_OBJ) {
		mouse_updateDraw = { mX, mY, OBJ_TEST::w, OBJ_TEST::h };
		current_enemy->setRenderPos(mX, mY);
		current_enemy->render(rn);
	}
}

void EDIT_AREA_LC::placingObjects_events(SDL_Renderer * rn)
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	if (Mouse::getRState())
		setMap_view();
	mouse_updateDraw = { mX, mY, OBJ_TEST::w, OBJ_TEST::h };
	test_objectTX.render(rn, nullptr, &mouse_updateDraw);
}

void EDIT_AREA_LC::movingMap_events()
{
	if (Mouse::getLState()) {
		//map_renderArea.setView();// objects_test);
	}
}

void EDIT_AREA_LC::selecingObjects_events()
{
	if (Mouse::getRState())
		setMap_view();
	for (auto & enemy : objects_test) {
		if (enemy.is_clicked()) {
			current_enemy = &enemy;
			edit_state = EditArea_LC_state::MOVING_OBJ;
			break;
		}
	}
}

void EDIT_AREA_LC::deletingObjects_events()
{
	for (auto & enemy : objects_test) {
		if (enemy.is_clicked()) {
			current_enemy = &enemy;
			break;
		}
	}
	if (current_enemy) {
		std::swap(*current_enemy, objects_test.back());
		objects_test.pop_back();
		current_enemy = nullptr;
	}
}

void EDIT_AREA_LC::movingOBJ_events(SDL_Renderer * rn)
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	if (Mouse::getRState())
		setMap_view();

	current_enemy->setRenderPos(mX, mY);

	current_enemy->render(rn);
}

void EDIT_AREA_LC::renderEnemies(SDL_Renderer * rn)
{
	static SDL_Rect Render_POS;
	static double scaleW, scaleH;

	for (auto & enemy : objects_test) {
		if (enemy.getX() >= map_renderArea.getPOS().x && enemy.getX() <= map_renderArea.getPOS().x + map_renderArea.getPOS().w
			&& enemy.getY() >= map_renderArea.getPOS().y && enemy.getY() <= map_renderArea.getPOS().y + map_renderArea.getPOS().h) 
		{
			enemy.render(rn);
		}
	}
}

void EDIT_AREA_LC::renderBlocks(SDL_Renderer * rn)
{

}

void EDIT_AREA_LC::events_enemies()
{
	for (auto & enemy : objects_test)
		enemy.events();
}

void EDIT_AREA_LC::createOBJ(const int & X, const int & Y)
{
	static int RenderPOS_X, RenderPOS_Y;
	static double scaleX, scaleY;

	scaleX = double(X - map_renderArea.getPOS().x) / double(map_renderArea.getPOS().w);
	scaleY = double(Y - map_renderArea.getPOS().y) / double(map_renderArea.getPOS().h);

	RenderPOS_X = round(scaleX * position.w) + position.x;
	RenderPOS_Y = round(scaleY * position.h) + position.y;

	objects_test.push_back({ X, Y }); // po³ó¿ obiekt wzglêdem textury mapy
	objects_test.back().setRenderPos(RenderPOS_X, RenderPOS_Y);
}

void EDIT_AREA_LC::on_buttonL_MouseClick(const int & mX, const int & mY)
{
	switch (edit_state)
	{
	case EditArea_LC_state::MOVING_OBJ:
		static double scaleX, scaleY;
		static int point_mapX, point_mapY;

		scaleX = double(mX - position.x) / position.w;
		scaleY = double(mY - position.y) / position.h;

		point_mapX = map_renderArea.getPOS().x + round(map_renderArea.getPOS().w * scaleX);
		point_mapY = map_renderArea.getPOS().y + round(map_renderArea.getPOS().h * scaleY);

		current_enemy->set_mapPOS(point_mapX, point_mapY);
		current_enemy = nullptr;
		edit_state = EditArea_LC_state::MOVING_MAP;
		break;
	case EditArea_LC_state::PLACING_OBJ:
		static double scaleTX_w, scaleTX_h;
		static double renderScaleObj_X, renderScaleObj_Y;

		static int x, y;

		scaleTX_w = double(mX - position.x) / position.w;
		scaleTX_h = double(mY - position.y) / position.h;

		x = map_renderArea.getPOS().x + round(map_renderArea.getPOS().w * scaleTX_w);
		y = map_renderArea.getPOS().y + round(map_renderArea.getPOS().h * scaleTX_h);

		createOBJ(x, y);
		break;
	}
}

void EDIT_AREA_LC::on_buttonL_MousePress(const int & mX, const int & mY)
{

}

OBJ_TEST::OBJ_TEST(const int & x1, const int & y1)
	: x{ x1 }, y{ y1 }
{
	render_position.w = w;
	render_position.h = h;

	data = { x, y };
};

/*void OBJ_TEST::setID(std::list<OBJ_TEST>::iterator iterator)
{
	ID = iterator;
}*/

void OBJ_TEST::setPOS(const SDL_Rect & rt)
{
	x = rt.x;
	y = rt.y;
}

void OBJ_TEST::set_mapPOS(const int & X, const int & Y)
{
	x = X;
	y = Y;

	data.x = X;
	data.y = Y;
}

void OBJ_TEST::setRenderPos(const int & render_X, const int & render_Y)
{
	render_position.x = render_X;
	render_position.y = render_Y;
}

void OBJ_TEST::events()
{
	mouse_handler();
}

void OBJ_TEST::mouse_handler()
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	clicked = false;

	if (mX >= render_position.x && mX <= render_position.x + render_position.w
		&& mY >= render_position.y && mY <= render_position.y + render_position.h)
	{
		if (Mouse::getButtonState() == Mouse_key::L_BUTTON && !clicked)
			clicked = true;
		else if (Mouse::getButtonState() == Mouse_key::NONE)
			clicked = false;
	}
}

void OBJ_TEST::setTexture(const std::string & bg)
{
	TX.loadFromFile(bg); // tylko dla testu - textura nie mo¿e byæ statyczna, gdy¿ ka¿dy obiekt bêdzie móg³ mieæ przerzut poziomy(odwrócenie textury w prawo, w lewo itd.)
}

void OBJ_TEST::render(SDL_Renderer * rn)
{
	TX.render(rn, nullptr, &render_position);
}

void Map_area::Init(const SDL_Rect & rt)
{
	area = rt;
}

void Map_area::setScale(const double & Scale)
{
	scale = Scale;
}

bool Map_area::canMove_r()
{
	if (area.x + area.w < TX->getWidth())
		return true;
	return false;
}

bool Map_area::canMove_l()
{
	if (area.x > 0)
		return true;
	return false;
}

bool Map_area::canMove_u()
{
	if (area.y > 0)
		return true;
	return false;
}

bool Map_area::canMove_d()
{
	if (area.y + area.h > TX->getHeight())
		return true;
	return false;
}