#include "Map_EditArea.h"
#include "LevelEditor_manager.h"
#include "Video_Info.h"
#include "Mouse.h"
#include "Map_EditArea_manager.h"
#include "Enemy_Test.h"
#include "Renderer.h"
#include "Enemy_TEST2.h"

/* test
#include <iostream>
using std::cout;
using std::endl;
// end test*/

Map_EditArea::Map_EditArea(const SDL_Rect & pos) :
	mouse_over{ false },
	multi_selecting_area{}
{
	edit_area.x = round(pos.x * Video_Info::get_scaleW());
	edit_area.y = round(pos.y * Video_Info::get_scaleH());
	edit_area.w = round(pos.w * Video_Info::get_scaleW());
	edit_area.h = round(pos.h * Video_Info::get_scaleH());
}

void Map_EditArea::save_Objects(const std::string & name)
{
	using std::ios_base;

	save.open(name.c_str(), ios_base::out | ios_base::binary);

	if (save.is_open()) {
		for (auto & enemy : enemies)
			save.write(reinterpret_cast<const char*>(&enemy->getData()), sizeof(enemy->getData()));
	}
	save.close();

	// to powinno byæ zrobione w klasie Level Creator, ale jest tutaj dla testów
	save.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".properties").c_str(), ios_base::out | ios_base::binary);
	save.write(LevelEditor_manager::get_backgroundName().c_str(), LevelEditor_manager::get_backgroundName().size());//sizeof(LevelEditor_manager::get_levelName().c_str()));
	save.close();
}

void Map_EditArea::load_Objects(const std::string & name)
{
	using std::ios_base;

	reset();


	char nazwa[100]{};

	load.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".properties").c_str(), ios_base::in | ios_base::binary);
	load.read(nazwa, 100);
	load.close();
	LevelEditor_manager::set_backgroundName(nazwa);

	set_background(LevelEditor_manager::get_levels_mapsPath() + nazwa + ".png");

	load.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName()).c_str(), ios_base::in | ios_base::binary);

	if (load.is_open()) {
		while (load.read(reinterpret_cast<char*>(&enemy_data), sizeof(Enemy_data)))
			create_EnemyOBJ(enemy_data.mapX, enemy_data.mapY, enemy_data.id, enemy_data.flip);
	}
	load.close();
}

void Map_EditArea::events()
{
	if (Map_EditArea_manager::getMain_state() == Map_EditArea_state::DELETE_OBJECTS) {
		deleting_objects_events();
	}

	mouse_handler(); // wszystkie zale¿ne zdarzenia od myszki i klawiatury
}

void Map_EditArea::events_indp()
{
	events_enemies();
	switch (Map_EditArea_manager::getMain_state()) {
	case Map_EditArea_state::SELECTING_OBJECTS:
		switch (Map_EditArea_manager::getSelect_satate()) {
		case Selecting_Obj_state::SINGLE:
			for (auto & enemy : enemies) {
				if (enemy->is_clicked()) {
					if (!enemy->is_selected()) {
						current_enemy = enemy;
						enemy->switch_selected_state();
						Map_EditArea_manager::setMain_state(Map_EditArea_state::PLACING_OBJECTS);
					}
					else
						enemy->switch_selected_state();
					break;
				}
			}
			break;
		case Selecting_Obj_state::MULTI:
			multi_selecingObject_events();
			break;
		}
		break;
	case Map_EditArea_state::PLACING_OBJECTS:
		if (current_enemy)
			current_enemy->set_position(Mouse::getX(), Mouse::getY()); // przed tym trzeba zapisaæ kopiê wczesniejszej pozycji
		break;
	case Map_EditArea_state::DELETE_OBJECTS:
		deleting_objects_events();
		break;
	}
}

void Map_EditArea::render()
{
	render_map();
	render_enemies();

	switch (Map_EditArea_manager::getMain_state()) {
	case Map_EditArea_state::PLACING_OBJECTS:
		if (!current_enemy)
			Map_EditArea_manager::render_tempOBJ();
		else
			current_enemy->render();
		break;
	case Map_EditArea_state::SELECTING_OBJECTS:
		switch (Map_EditArea_manager::getSelect_satate()) {
		case Selecting_Obj_state::SINGLE:
			break;
		case Selecting_Obj_state::MULTI:
			SDL_SetRenderDrawColor(Renderer::get(), 0, 0, 255, 255);
			SDL_RenderDrawRect(Renderer::get(), &multi_selecting_area);
			SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
			break;
		}
		break;
	}
}

void Map_EditArea::set_background(const std::string & bg)
{
	Map_EditArea_manager::set_Background_name(bg);

	mapBG.loadFromFile(bg);

	mapBG_area.x = 0;
	mapBG_area.y = 0;

	double scale = double(mapBG.getHeight()) / double(Video_Info::getWindow_H());

	mapBG_area.w = round(mapBG.getWidth() * scale);
	mapBG_area.h = mapBG.getHeight();
}

void Map_EditArea::mouse_handler()
{
	static const int & mX = Mouse::getX();
	static const int & mY = Mouse::getY();

	mouse_over = false;

	if (Mouse::getX() >= edit_area.x && Mouse::getX() <= edit_area.x + edit_area.w
		&& Mouse::getY() >= edit_area.y && Mouse::getY() <= edit_area.y + edit_area.h) 
	{
		mouse_over = true;
		if (Mouse::getBt_state() == Mouse_key::L_BUTTON) { // pojedyncze klikniêcie
			switch (Map_EditArea_manager::getMain_state())
			{
			case Map_EditArea_state::PLACING_OBJECTS:
				placing_mouseL_Events(); // zdarzenia dla klikniêcia lewego przycisku myszy
				break;
			case Map_EditArea_state::SELECTING_OBJECTS:
				switch (Map_EditArea_manager::getSelect_satate()) {
				case Selecting_Obj_state::SINGLE:
					break;
				case Selecting_Obj_state::MULTI:
					// test
					//system("cls");
					// end test
					multi_selecting_area.x = Mouse::get_clickedPoint().x;
					multi_selecting_area.y = Mouse::get_clickedPoint().y;
					break;
				}
			}
		}

		if (Mouse::is_pressedL()) { // przytrzymanie lewego klawisza myszy
			switch (Map_EditArea_manager::getMain_state()) {
			case Map_EditArea_state::MOVING_MAP:
				move_map_Mouse();
				break;
			case Map_EditArea_state::SELECTING_OBJECTS:
				switch (Map_EditArea_manager::getSelect_satate()) {
				case Selecting_Obj_state::SINGLE:
					break;
				case Selecting_Obj_state::MULTI:
					multi_selecingObject_mouseEvents();
					break;
				}

				break;
			}
		}
		else if (Mouse::getBt_state() == Mouse_key::R_BUTTON) {
			switch (Map_EditArea_manager::getMain_state()) {
			case Map_EditArea_state::PLACING_OBJECTS:
				placing_mouseR_Events();
				break;
			case Map_EditArea_state::SELECTING_OBJECTS:

				break;
			case Map_EditArea_state::MOVING_MAP: // stan do przesuwania mapy myszk¹ naciskaj¹c lewy klawisz myszy

				break;
			}
		}
		if (Mouse::getWheelState() != Mouse_wheel::NONE)
			move_map_Wheel();
	}
}

void Map_EditArea::reset()
{
	enemies.clear();
	Map_EditArea_manager::reset();
}

void Map_EditArea::placing_objects_events()
{

}

void Map_EditArea::multi_selecingObject_events()
{
	// jak na razie tylko dla enemies

	for (auto & enemy : enemies) {
		if (enemy->get_renderPOS().x > multi_selecting_area.x && enemy->get_renderPOS().y > multi_selecting_area.y
			&& enemy->get_renderPOS().x + enemy->get_renderPOS().w < multi_selecting_area.x + multi_selecting_area.w && enemy->get_renderPOS().y + enemy->get_renderPOS().h < multi_selecting_area.y + multi_selecting_area.h)
		{
			enemy->set_selectState(true);
			//cout << "Zaznaczono obiekt na pozycji: x: " << enemy->get_renderPOS().x << " y: " << enemy->get_renderPOS().y << endl;
		}
		else
			enemy->set_selectState(false);
	}

	const Uint8 * keyboard = SDL_GetKeyboardState(nullptr);

	if (keyboard[SDL_SCANCODE_DELETE]) {
		for (int i = 0; i != enemies.size(); i++) {
			if (enemies[i]->is_selected()) {
				std::swap(enemies[i], enemies.back());
				enemies.pop_back();
				i--;
			}
		}

	}

}

void Map_EditArea::moving_objects_events()
{

}

void Map_EditArea::placing_mouseL_Events()
{
	static double scaleTX_w, scaleTX_h;
	static int x, y;

	scaleTX_w = double(Mouse::getX() - edit_area.x) / edit_area.w;
	scaleTX_h = double(Mouse::getY() - edit_area.y) / edit_area.h;

	x = mapBG_area.x + round(mapBG_area.w * scaleTX_w);
	y = mapBG_area.y + round(mapBG_area.h * scaleTX_h);

	if (!current_enemy) {
		switch (Map_EditArea_manager::get_OBJ_type())
		{
		case OBJ_type::ENEMY:
			create_EnemyOBJ(x, y, Map_EditArea_manager::get_EnemyID(), Map_EditArea_manager::get_OBJ_orient()); // przy dzia³aniu programu i przy ³adowaniu z pliku
			break;
		}
	}
	else {
		// na razie tylko dla obiektów "enemy" - dla testów
		int RenderPOS_X = round(scaleTX_w * edit_area.w) + edit_area.x;
		int RenderPOS_Y = round(scaleTX_h * edit_area.h) + edit_area.y;

		current_enemy->set_mapPOS(x, y);
		current_enemy->set_position(RenderPOS_X, RenderPOS_Y);
		current_enemy = nullptr;
		Map_EditArea_manager::switch_to_prev_state();
	}
}

void Map_EditArea::placing_mouseR_Events()
{
	if (!current_enemy)
		Map_EditArea_manager::switch_OBJ_orient();
	else
		current_enemy->switch_orient();
}

void Map_EditArea::create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip)
{
	static int RenderPOS_X, RenderPOS_Y;
	static double scaleX, scaleY;

	scaleX = double(X - mapBG_area.x) / double(mapBG_area.w);
	scaleY = double(Y - mapBG_area.y) / double(mapBG_area.h);

	RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
	RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

	switch (id)
	{
	case Enemy_ID::TEST:
		enemies.push_back(new Enemy_Test{ X, Y, flip });
		break;
	case Enemy_ID::TEST2:
		enemies.push_back(new Enemy_TEST2{ X, Y, flip });
		break;
	}
	enemies.back()->set_position(RenderPOS_X, RenderPOS_Y);
}

void Map_EditArea::events_enemies()
{
	for (auto & enemy : enemies)
		enemy->events();
}

void Map_EditArea::render_map()
{
	mapBG.render(&mapBG_area, &edit_area);

	SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::get(), &edit_area);
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}

void Map_EditArea::render_enemies()
{
	for (auto & enemy : enemies) {
		if (enemy->get_mapX() >= mapBG_area.x && enemy->get_mapX() <= mapBG_area.x + mapBG_area.w
			&& enemy->get_mapY() >= mapBG_area.y && enemy->get_mapY() <= mapBG_area.y + mapBG_area.h)
		{
			enemy->render();
		}
	}
}

void Map_EditArea::multi_selecingObject_mouseEvents()
{
	static const int & mX = Mouse::getX();
	static const int & mY = Mouse::getY();

	multi_selecting_area.w = std::abs(mX - multi_selecting_area.x);
	multi_selecting_area.h = std::abs(mY - multi_selecting_area.y);
}

void Map_EditArea::single_selecingObject_events()
{

}

void Map_EditArea::deleting_objects_events()
{
	for (auto & enemy : enemies) {
		if (enemy->is_clicked()) {
			std::swap(enemy, enemies.back());
			enemies.pop_back();
			break;
		}
	}
	/*for (int i = 0; i != enemies.size(); i++) {
		if (enemies[i]->is_clicked()) {
			std::swap(enemies[i], enemies.back());
			enemies.pop_back();
			i--;
		}
	}*/
}

void Map_EditArea::move_map_Wheel()
{
	if (Mouse::getWheelState() == Mouse_wheel::UP || Mouse::getWheelState() == Mouse_wheel::DOWN)
	{
		if (Mouse::getWheelState() == Mouse_wheel::UP && mapBG_area.x + mapBG_area.w < mapBG.getWidth()) {
			if (mapBG_area.x + MAP_MOVE_SIZE + mapBG_area.w < mapBG.getWidth())
				mapBG_area.x += MAP_MOVE_SIZE;
			else
				mapBG_area.x = mapBG.getWidth() - mapBG_area.w;
		}
		else if (Mouse::getWheelState() == Mouse_wheel::DOWN && mapBG_area.x > 0) {

			if (mapBG_area.x - MAP_MOVE_SIZE > 0)
				mapBG_area.x -= MAP_MOVE_SIZE;
			else
				mapBG_area.x = 0;
		}

		for (auto & enemy : enemies) {
			static int RenderPOS_X, RenderPOS_Y;
			static double scaleX, scaleY;

			scaleX = double(enemy->get_mapX() - mapBG_area.x) / double(mapBG_area.w);
			scaleY = double(enemy->get_mapY() - mapBG_area.y) / double(mapBG_area.h);

			RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
			RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

			enemy->set_position(RenderPOS_X, RenderPOS_Y);
		}
	}
}

void Map_EditArea::move_map_Mouse()
{
	static double scaleX, scale_recentX;
	static double scaleY, scale_recentY;

	static int pointX, point_recentX;

	static int maprender_absX, maprender_absY;

	if (Mouse::getX() < Mouse::getR_x() || Mouse::getX() > Mouse::getR_x()
		|| Mouse::getY() < Mouse::getR_y() || Mouse::getY() > Mouse::getY())
	{
		scaleX = double(Mouse::getX() - edit_area.x) / double(edit_area.w);
		scale_recentX = double(Mouse::getR_x() - edit_area.x) / double(edit_area.w);

		pointX = mapBG_area.x + round(mapBG_area.w * scaleX);
		point_recentX = mapBG_area.x + round(mapBG_area.w * scale_recentX);

		maprender_absX = abs(pointX - point_recentX);

		if (Mouse::getX() < Mouse::getR_x() && mapBG_area.x + mapBG_area.w < mapBG.getWidth()) {
			if (mapBG_area.x + maprender_absX + mapBG_area.w < mapBG.getWidth())
				mapBG_area.x += maprender_absX;
			else
				mapBG_area.x = mapBG.getWidth() - mapBG_area.w;
		}
		else if (Mouse::getX() > Mouse::getR_x() && mapBG_area.x > 0) {

			if (mapBG_area.x - maprender_absX > 0)
				mapBG_area.x -= maprender_absX;
			else
				mapBG_area.x = 0;
		}

		for (auto & enemy : enemies) {
			static int RenderPOS_X, RenderPOS_Y;

			scaleX = double(enemy->get_mapX() - mapBG_area.x) / double(mapBG_area.w);
			scaleY = double(enemy->get_mapY() - mapBG_area.y) / double(mapBG_area.h);

			RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
			RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

			enemy->set_position(RenderPOS_X, RenderPOS_Y);
		}
	}
}