#include "EDIT_AREA_LC.h"
#include "Mouse.h"

Texture OBJ_TEST::TX{};

void EDIT_AREA_LC::Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	level_name = "data/levels/saves/level_test.txt";

	setPOS(dm, scaleW, scaleH); // ustala pozycjê
	test_objectTX.loadFromFile("data/textures/test.png");
	OBJ_TEST::setTexture("data/textures/test.png");
}

void EDIT_AREA_LC::load_MAP(const std::string & bg)
{
	mapBG.loadFromFile(bg);
}

void EDIT_AREA_LC::saveLevel()
{
	using std::endl;

	save.open(level_name.c_str());
	if (save.is_open()) {
		save << "ENEMY:" << endl;
		for (auto & enemy : objects_test)
			save << enemy.getX() << ' ' << enemy.getY() << endl;
	}
	save.close();
}

void EDIT_AREA_LC::loadLevel()
{
	clearALL();

	load.open(level_name.c_str());

	if (load.is_open()) {
		int x, y;
		std::string OBJ;
		load >> OBJ;
		while (load >> x >> y)
			createOBJ(x, y);
	}
	load.close();
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
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	if (mX >= position.x && mX <= position.x + position.w
		&& mY >= position.y && mY <= position.y + position.h)
	{
		if (Mouse::getButtonState() == Mouse_key::L_BUTTON && !lBT_clicked)
		{
			if (edit_state == EditArea_LC_state::PLACING_OBJ) {
				createOBJ(mX, mY);
				lBT_clicked = true;
			}
			else if (edit_state == EditArea_LC_state::MOVING_OBJ) {
				current_enemy = nullptr;
				edit_state = EditArea_LC_state::NONE;
			}
		}
		else if (Mouse::getButtonState() == Mouse_key::NONE)
			lBT_clicked = false;
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

void EDIT_AREA_LC::renderBackground(SDL_Renderer * rn)
{
	mapBG.render(rn, nullptr, &position);
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
	for (auto & enemy : objects_test)
		if (enemy.is_clicked())
			current_enemy = &enemy;
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
	objects_test.push_back({ mX, mY }); // po³ó¿ obiekt wzglêdem obszaru edycji
	objects_test.back().setID(--objects_test.end()); // ustala ID za pomoc¹ odpowiedniego iteratora
}

OBJ_TEST::OBJ_TEST(int x1, int y1) :
	x{ x1 }, y{ y1 }
{
	position = { x, y, w, h };
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

void OBJ_TEST::setTexture(std::string bg)
{
	TX.loadFromFile(bg); // tylko dla testu - textura nie mo¿e byæ statyczna, gdy¿ ka¿dy obiekt bêdzie móg³ mieæ przerzut poziomy(odwrócenie textury w prawo, w lewo itd.)
}

void OBJ_TEST::render(SDL_Renderer * rn)
{
	TX.render(rn, nullptr, &position);
}