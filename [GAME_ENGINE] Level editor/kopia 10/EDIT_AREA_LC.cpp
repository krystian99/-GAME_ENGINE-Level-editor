#include "EDIT_AREA_LC.h"
#include "Mouse.h"

Texture EDIT_AREA_LC::OBJ_TEST::TX{};

void EDIT_AREA_LC::Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	setPOS(dm, scaleW, scaleH); // ustala pozycjê
	test_objectTX.loadFromFile("data/textures/test.png");
	OBJ_TEST::setTexture("data/textures/test.png");
}

void EDIT_AREA_LC::load_MAP(const std::string & bg)
{
	mapBG.loadFromFile(bg);
}

void EDIT_AREA_LC::clearALL()
{
	objects_test.clear();
}

void EDIT_AREA_LC::events(SDL_Renderer * rn)
{
	render_ALL(rn);
	
	events_enemies(rn);

	switch (edit_state)
	{
	case EditArea_LC_state::SELECTING_OBJ:
		selecingObjects_events(rn);
		break;
	case EditArea_LC_state::MOVING_OBJ:
		//movingMap_events(rn);
		break;
	case EditArea_LC_state::MOVING_MAP:
		movingMap_events(rn);
		break;
	case EditArea_LC_state::PLACING_OBJ:
		placingObjects_events(rn);
		break;
	case EditArea_LC_state::DELETING_OBJ:
		deletingObjects_events(rn);
		break;
	}

	mouse_handler(rn);
}

void EDIT_AREA_LC::mouse_handler(SDL_Renderer * rn)
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	if (mX >= position.x && mX <= position.x + position.w
		&& mY >= position.y && mY <= position.y + position.h)
	{
		if (edit_state == EditArea_LC_state::PLACING_OBJ) {
			if (Mouse::get_lButton_State() && !lBT_clicked) {
				objects_test.push_back({ mX, mY, int(objects_test.size()) }); // po³ó¿ obiekt wzglêdem obszaru edycji
				lBT_clicked = true;
			}
			else if (!Mouse::get_lButton_State())
				lBT_clicked = false;
			/*if (Mouse::get_rButton_State())
				; // przerzuæ obiekt poziomo*/
		}
		if (edit_state == EditArea_LC_state::MOVING_MAP) {

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

void EDIT_AREA_LC::renderBackground(SDL_Renderer * rn)
{
	mapBG.render(rn, nullptr, &position);
}

void EDIT_AREA_LC::render_ALL(SDL_Renderer * rn)
{
	renderBackground(rn);
	//renderEnemies(rn);
	renderBlocks(rn);

	SDL_SetRenderDrawColor(rn, 255, 0, 0, 255);
	SDL_RenderDrawRect(rn, &position);
	SDL_SetRenderDrawColor(rn, 255, 255, 255, 255);
}

void EDIT_AREA_LC::placingObjects_events(SDL_Renderer * rn)
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	mouse_updateDraw = { mX, mY, OBJ_TEST::w, OBJ_TEST::h };
	test_objectTX.render(rn, nullptr, &mouse_updateDraw);
}

void EDIT_AREA_LC::movingMap_events(SDL_Renderer * rn)
{

}

void EDIT_AREA_LC::selecingObjects_events(SDL_Renderer * rn)
{

}

void EDIT_AREA_LC::deletingObjects_events(SDL_Renderer * rn)
{
	for (auto & enemy : objects_test) {
		if (enemy.is_clicked())
			currentOBJ_ID = enemy.getID();
	}
	objects_test.erase(objects_test.begin() + currentOBJ_ID);
}

void EDIT_AREA_LC::renderEnemies(SDL_Renderer * rn)
{
	for (auto & enemy : objects_test)
		enemy.render(rn);
}

void EDIT_AREA_LC::renderBlocks(SDL_Renderer * rn)
{
	
}

void EDIT_AREA_LC::events_enemies(SDL_Renderer * rn)
{
	for (auto & enemy : objects_test)
		enemy.events(rn);
}

void EDIT_AREA_LC::OBJ_TEST::events(SDL_Renderer * rn)
{
	mouse_handler();
	render(rn);
}

void EDIT_AREA_LC::OBJ_TEST::mouse_handler()
{
	int mX = Mouse::getMousePOSx();
	int mY = Mouse::getMousePOSy();

	if (mX >= position.x && mX <= position.x + position.w
		&& mY >= position.y && mY <= position.y + position.h) 
	{
		if (Mouse::get_lButton_State() && !clicked)
			clicked = true;
		else if (!Mouse::get_lButton_State())
			clicked = false;
	}
}

void EDIT_AREA_LC::OBJ_TEST::setTexture(std::string bg)
{
	TX.loadFromFile(bg); // tylko dla testu - textura nie mo¿e byæ statyczna, gdy¿ ka¿dy obiekt bêdzie móg³ mieæ przerzut poziomy(odwrócenie textury w prawo, w lewo itd.)
}

void EDIT_AREA_LC::OBJ_TEST::render(SDL_Renderer * rn)
{
	//SDL_Rect pos;
	//pos = { x, y, w, h };
	TX.render(rn, nullptr, &position);
}