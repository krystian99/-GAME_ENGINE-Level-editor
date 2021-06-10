#include "EDIT_AREA_LC.h"
#include "Mouse.h"
Texture OBJ_TEST::TX{};

static const std::string levels_save_path = "data/levels/saves/";

void EDIT_AREA_LC::Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	setPOS(dm, scaleW, scaleH); // ustala pozycj�
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
		int x, y;
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
	int x = 20 * scaleW;
	int y = 80 * scaleH;
	int w = dm->w - (130 * scaleW) - x;
	int h = dm->h - (80 * scaleH) - y;

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
	map.w = mapBG.getWidth() * scale;


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

	render_eventsDependent(rn); // aktualizuje stan zdarzen i renderuje - tzw. renderowanie zale�ne od zdzarze�
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
		current_enemy->setPOS(mouse_updateDraw);
		current_enemy->render(rn);
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
		map_renderArea.setView();
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
	current_enemy->render(rn);
	if (Mouse::getRState())
		map_renderArea.setView();
}

void EDIT_AREA_LC::renderEnemies(SDL_Renderer * rn)
{
	for (auto & enemy : objects_test)
		enemy.render(rn);
}

void EDIT_AREA_LC::renderBlocks(SDL_Renderer * rn)
{
	
}

void EDIT_AREA_LC::events_enemies()
{
	for (auto & enemy : objects_test)
		enemy.events();
}

void EDIT_AREA_LC::createOBJ(int mX, int mY)
{
	objects_test.push_back({ mX, mY }); // po�� obiekt wzgl�dem obszaru edycji
	objects_test.back().setID(--objects_test.end()); // ustala ID za pomoc� odpowiedniego iteratora
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
		createOBJ(mX, mY);
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

OBJ_TEST::OBJ_TEST(int x1, int y1) :
	x{ x1 }, y{ y1 }
{
	position = { x, y, w, h };
	data = { x, y };
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
	TX.loadFromFile(bg); // tylko dla testu - textura nie mo�e by� statyczna, gdy� ka�dy obiekt b�dzie m�g� mie� przerzut poziomy(odwr�cenie textury w prawo, w lewo itd.)
}

void OBJ_TEST::render(SDL_Renderer * rn)
{
	TX.render(rn, nullptr, &position);
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
	if (Mouse::getMousePOSx() < Mouse::getRecent_x() && canMove_r())
		area.x += abs(Mouse::getMousePOSx() - Mouse::getRecent_x());
	if (Mouse::getMousePOSx() > Mouse::getRecent_x() && canMove_l())
		area.x -= abs(Mouse::getMousePOSx() - Mouse::getRecent_x());
	if (Mouse::getMousePOSy() < Mouse::getRecent_y() && canMove_u())
		area.y += abs(Mouse::getMousePOSy() - Mouse::getRecent_y());
	if (Mouse::getMousePOSy() > Mouse::getRecent_y() && canMove_d())
		area.y -= abs(Mouse::getMousePOSy() - Mouse::getRecent_y());
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
	if (area.y > 0 )
		return true;
	return false;
}

bool Map_area::canMove_d()
{
	if (area.y + area.h > TX->getHeight())
		return true;
	return false;
}