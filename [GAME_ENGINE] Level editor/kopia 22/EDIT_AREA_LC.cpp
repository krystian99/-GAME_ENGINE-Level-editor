#include "EDIT_AREA_LC.h"
#include "Mouse.h"
#include <cmath>

Texture OBJ_TEST::TX{};

static const std::string levels_save_path = "data/levels/saves/";

void EDIT_AREA_LC::Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	scaleScreenW = scaleW;
	scaleScreenH = scaleH;

	disp = dm;
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
		//int x, y;
		while (load.read(reinterpret_cast<char*>(&data_object_test), sizeof(data_object_test)))
			createOBJ(data_object_test.x, data_object_test.y);// , data_object_test.renderScaleX, data_object_test.renderScaleY);
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
		if (Mouse::getButtonState() == Mouse_key::L_BUTTON)
		{
			if (edit_state == EditArea_LC_state::MOVING_MAP)
				moving_map = true;
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
		/*mouse_updateDraw = { mX, mY, OBJ_TEST::w, OBJ_TEST::h };
		current_enemy->setPOS(mouse_updateDraw);
		current_enemy->render(rn);*/

		mouse_updateDraw = { mX, mY, OBJ_TEST::w, OBJ_TEST::h };
		current_enemy->setPOS(mouse_updateDraw);

		//int RenderPOS_X = position.w * current_enemy->getScaleX() + position.x;
		//int RenderPOS_Y = position.h * current_enemy->getScaleY() + position.y;

		current_enemy->render(rn);// , RenderPOS_X, RenderPOS_Y);
	}
}

void EDIT_AREA_LC::placingObjects_events(SDL_Renderer * rn)
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	mouse_updateDraw = { mX, mY, OBJ_TEST::w, OBJ_TEST::h };
	test_objectTX.render(rn, nullptr, &mouse_updateDraw);
}

void EDIT_AREA_LC::movingMap_events()
{
	if (Mouse::getLState()) {
		map_renderArea.setView(objects_test);
	}
}

void EDIT_AREA_LC::selecingObjects_events()
{
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
		objects_test.erase(current_enemy->getID());
		current_enemy = nullptr;
	}
}

void EDIT_AREA_LC::movingOBJ_events(SDL_Renderer * rn)
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	mouse_updateDraw = { mX, mY, OBJ_TEST::w, OBJ_TEST::h };
	current_enemy->setPOS(mouse_updateDraw);
	//current_enemy->render(rn);

	//int RenderPOS_X = position.w * current_enemy->getScaleX() + position.x;
	//int RenderPOS_Y = position.h * current_enemy->getScaleY() + position.y;

	current_enemy->render(rn);// , RenderPOS_X, RenderPOS_Y);

	if (Mouse::getRState())
		map_renderArea.setView(objects_test);
}

void EDIT_AREA_LC::renderEnemies(SDL_Renderer * rn)
{
	//static const double scaleX = position.w / map_renderArea.getPOS().w;
	//static const double scaleH = position.h / map_renderArea.getPOS().h;

	static SDL_Rect Render_POS;
	static double scaleW, scaleH;

	for (auto & enemy : objects_test) {
		if (enemy.getX() >= map_renderArea.getPOS().x && enemy.getX() <= map_renderArea.getPOS().x + map_renderArea.getPOS().w
			&& enemy.getY() >= map_renderArea.getPOS().y && enemy.getY() <= map_renderArea.getPOS().y + map_renderArea.getPOS().h) 
		{
			//scaleW = double(enemy.getX() - map_renderArea.getPOS().x) / double(map_renderArea.getPOS().w);
			//scaleH = double(enemy.getY() - map_renderArea.getPOS().y) / double(map_renderArea.getPOS().h);

			//int RenderPOS_X = position.w * enemy.getScaleX() + position.x;
			//int RenderPOS_Y = position.h * enemy.getScaleY() + position.y;

			enemy.render(rn);// , RenderPOS_X, RenderPOS_Y);
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

void EDIT_AREA_LC::createOBJ(int X, int Y)// , const double & scaleX, const double & scaleY)
{
	static int RenderPOS_X, RenderPOS_Y;
	static double scaleX, scaleY;
	/*RenderPOS_X = round(position.w * scaleX) + position.x;
	RenderPOS_Y = round(position.h * scaleY) + position.y;*/

	scaleX = double(X - map_renderArea.getPOS().x) / double(map_renderArea.getPOS().w);
	scaleY = double(Y - map_renderArea.getPOS().y) / double(map_renderArea.getPOS().h);

	RenderPOS_X = round(scaleX * position.w) + position.x;
	RenderPOS_Y = round(scaleY * position.h) + position.y;

	objects_test.push_back({ X, Y, scaleX, scaleY}); // po³ó¿ obiekt wzglêdem obszaru edycji
	objects_test.back().setID(--objects_test.end()); // ustala ID za pomoc¹ odpowiedniego iteratora
	objects_test.back().setRenderPos(RenderPOS_X, RenderPOS_Y);
}

void EDIT_AREA_LC::on_buttonL_MouseClick(const int & mX, const int & mY)
{
	switch (edit_state)
	{
	case EditArea_LC_state::MOVING_OBJ:
		current_enemy = nullptr;
		edit_state = EditArea_LC_state::NONE;
		break;
	case EditArea_LC_state::PLACING_OBJ:
		//static double scaleTX_w, scaleTX_h;
		static double renderScaleObj_X, renderScaleObj_Y;

		static int x, y;

		/*scaleTX_w = double(mX - position.x) / position.w;
		scaleTX_h = double(mY - position.y) / position.h;*/

		x = map_renderArea.getPOS().x + round(map_renderArea.getPOS().w * scaleTX_w);
		y = map_renderArea.getPOS().y + round(map_renderArea.getPOS().h * scaleTX_h);

		createOBJ(x, y);// , scaleTX_w, scaleTX_h);
		break;
	}
}

void EDIT_AREA_LC::on_buttonL_MousePress(const int & mX, const int & mY)
{
	switch (edit_state)
	{
	case EditArea_LC_state::MOVING_MAP:
		if (Mouse::getMousePOSx() < Mouse::getRecent_x() || Mouse::getMousePOSx() > Mouse::getRecent_x()
			|| Mouse::getMousePOSy() < Mouse::getRecent_y() || Mouse::getMousePOSy() > Mouse::getRecent_y())
		{
			map_renderArea.setView();
		}
		break;
	}
}

OBJ_TEST::OBJ_TEST(const int & x1, const int & y1, const double & scaleX, const double & scaleY) :
	x{ x1 }, y{ y1 }, ScaleX{ scaleX }, ScaleY{ scaleY }
{

	position = { x, y, w, h };

	render_position.w = position.w;
	render_position.h = position.h;

	data = { x, y, ScaleX, ScaleY };
}

void OBJ_TEST::setID(std::list<OBJ_TEST>::iterator iterator)
{
	ID = iterator;
}

void OBJ_TEST::setPOS(const SDL_Rect & rt)
{
	position = rt;
	x = rt.x;
	y = rt.y;
}

void OBJ_TEST::setRenderPos(const int & render_X, const int & render_Y)
{
	render_position.x = render_X;
	render_position.y = render_Y;
}

void OBJ_TEST::move_renderX(int sizeX)
{
	render_position.x += sizeX;
}

void OBJ_TEST::move_renderY(int sizeY)
{
	render_position.y += sizeY;
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

	if (mX >= position.x && mX <= position.x + position.w
		&& mY >= position.y && mY <= position.y + position.h)
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

void OBJ_TEST::render(SDL_Renderer * rn)//, const int & posX, const int & posY)
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

void Map_area::setView()
{
	static int absolute;
	if (Mouse::getMousePOSx() < Mouse::getRecent_x() && canMove_r()) {
		absolute = abs(Mouse::getMousePOSx() - Mouse::getRecent_x());

		if (area.x + absolute + area.w < TX->getWidth())
			area.x += absolute;
		else
			area.x = TX->getWidth() - area.w;
	}
	else if (Mouse::getMousePOSx() > Mouse::getRecent_x() && canMove_l()) {

		absolute = abs(Mouse::getMousePOSx() - Mouse::getRecent_x());

		if (area.x - absolute > 0)
			area.x -= absolute;
		else
			area.x = 0;
	}
	if (Mouse::getMousePOSy() < Mouse::getRecent_y() && canMove_d()) {
		absolute = abs(Mouse::getMousePOSy() - Mouse::getRecent_y());

		if (area.y + absolute + area.h < TX->getHeight())
			area.y += absolute;
		else
			area.y = TX->getHeight() - area.h;
	}
	else if (Mouse::getMousePOSy() > Mouse::getRecent_y() && canMove_u()) {
		absolute = abs(Mouse::getMousePOSy() - Mouse::getRecent_y());

		if (area.y - absolute > 0)
			area.y -= absolute;
		else
			area.y -= 0;
	}
}

void Map_area::setView(std::list<OBJ_TEST>& objects) // trzeba ustaliæ pozycjê renderowania tak samo jak przy tworzeniu obiektu
{
	static int absolute;
	static int size;

	if (Mouse::getMousePOSx() < Mouse::getRecent_x() && canMove_r()) {
		absolute = abs(Mouse::getMousePOSx() - Mouse::getRecent_x());

		if (area.x + absolute + area.w < TX->getWidth()) {
			area.x += absolute;
			for (auto & e : objects)
				e.move_renderX(-absolute);
		}
		else {
			size = TX->getWidth() - area.w;
			area.x = size;

			for (auto & e : objects)
				e.move_renderX(-size);
		}
	}
	else if (Mouse::getMousePOSx() > Mouse::getRecent_x() && canMove_l()) {

		absolute = abs(Mouse::getMousePOSx() - Mouse::getRecent_x());

		if (area.x - absolute > 0) {
			area.x -= absolute;
			for (auto & e : objects)
				e.move_renderX(absolute);
		}
		else {
			for (auto & e : objects)
				e.move_renderX(area.x);
			area.x = 0;
		}
	}
	if (Mouse::getMousePOSy() < Mouse::getRecent_y() && canMove_d()) {
		absolute = abs(Mouse::getMousePOSy() - Mouse::getRecent_y());

		if (area.y + absolute + area.h < TX->getHeight()) {
			area.y += absolute;
			for (auto & e : objects)
				e.move_renderY(absolute);
		}
		else {
			size = TX->getHeight() - area.h;
			area.y = size;

			for (auto & e : objects)
				e.move_renderY(size);
		}
	}
	else if (Mouse::getMousePOSy() > Mouse::getRecent_y() && canMove_u()) {
		absolute = abs(Mouse::getMousePOSy() - Mouse::getRecent_y());

		if (area.y - absolute > 0) {
			area.y -= absolute;
			for (auto & e : objects)
				e.move_renderY(-absolute);
		}
		else {
			for (auto & e : objects)
				e.move_renderY(-area.y);
			area.y = 0;
		}
	}
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