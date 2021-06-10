#include "Map.h"
#include "LevelEditor_manager.h"
#include "Video_Info.h"
#include "Mouse.h"
#include "Map_manager.h"
#include "Renderer.h"
#include "Enemy_Types.h"
#include "Engine_manager.h"

Map::Map(const SDL_Rect & pos) :
	enemy_placerModule{ enemies }
{
	edit_area.set(pos);
	Video_Info::set_scaledSize(edit_area.get());

	Map_manager::set_edit_area(edit_area.get().w, edit_area.get().h);
	multiOBJ_s.set(edit_area.get());
}

void Map::save_Objects(const std::string & name)
{
	using std::ios_base;
	std::ofstream save;

	save.open(name.c_str(), ios_base::out | ios_base::binary);

	if (save.is_open()) {
		for (auto & enemy : enemies)
			save.write(reinterpret_cast<const char*>(&enemy->getData()), sizeof(enemy->getData()));
	}
	save.close();
}

void Map::load_Objects(const std::string & name)
{
	reset();

	using std::ios_base;
	std::ifstream load;

	set_background(LevelEditor_manager::get_levels_mapsPath() + LevelEditor_manager::get_backgroundName() + ".png");

	load.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName()).c_str(), ios_base::in | ios_base::binary);

	if (load.is_open()) {
		while (load.read(reinterpret_cast<char*>(&enemy_data), sizeof(Enemy_data)))
			create_EnemyOBJ(enemy_data.mapPOS, enemy_data.id, enemy_data.flip);
	}
	load.close();
}

void Map::events() // zdarzenia zale¿ne od myszki(przyciski myszki: lewy, prawy, kó³ko)
{
	events_enemies();

	switch (Map_manager::getMain_state()) {
	case Map_state::SELECTING_OBJECTS:
		switch (Map_manager::getSelect_satate()) {
		case Selecting_Obj_state::SINGLE:
			single_selectingObject_events();
			break;
		}
		break;
	case Map_state::DELETE_OBJECTS:
		deleting_objects_events();
		break;
	}

	mouse_handler(); // wszystkie zale¿ne zdarzenia od myszki i klawiatury
}

void Map::events_indp()
{
	if (Map_manager::get_Update_state() != Map_Update_state::NONE)
		update_events();

	switch (Map_manager::getMain_state()) {
	case Map_state::SELECTING_OBJECTS:
		switch (Map_manager::getSelect_satate()) {
		case Selecting_Obj_state::MULTI:
			multi_selectingObject_events();
			break;
		}
		break;
	case Map_state::MOVING_OBJECT:
		singleOBJmove_s.events(mouse_over, edit_area.get());
		break;
	case Map_state::MULTI_MOVING_OBJECTS:
		// zdarzenia po nacisnieciu prawym klawiszem myszy na obszar zaznaczony do przeniesienia
		multiOBJ_s.events_moving(mouse_over, edit_area.get());
		break;
	case Map_state::SELECTING_OBJECTS_FINISHED:
		multiSelect_OBJs_set();
		break;
	}
}

void Map::render()
{
	render_map();
	render_enemies();

	switch (Map_manager::getMain_state()) {
	case Map_state::PLACING_OBJECTS:
		Map_manager::render_tempOBJ(edit_area.get().x, edit_area.get().y);
		break;
	case Map_state::MOVING_OBJECT:
		singleOBJmove_s.current_enemy->render();
		break;
	case Map_state::SELECTING_OBJECTS:
		switch (Map_manager::getSelect_satate()) {
		case Selecting_Obj_state::MULTI:
			/*Renderer::set_renderColor({ 0, 0, 255, 255 });
			SDL_RenderDrawRect(Renderer::get(), &multi_selecting_area);
			Renderer::set_defaultColor();*/

			//multiOBJ_s.render();
			multiOBJ_s.render(edit_area.get());
			break;
		}
		break;
	case Map_state::MULTI_MOVING_OBJECTS:
		multiOBJ_s.render(edit_area.get());
		break;
	}
}

void Map::set_background(const std::string & bg)
{
	Map_manager::set_Background_name(bg);

	mapBG.loadFromFile(bg);

	/*mapBG_area.x = 0;
	mapBG_area.y = 0;
	mapBG_area.h = mapBG.getHeight();*/

	mapBG_area.set(0, 0, -1, mapBG.getHeight());

	double scale = double(edit_area.get().h) / double(mapBG.getHeight());

	if (mapBG.getHeight() < edit_area.get().h)
	{
		/*int scaled_w = std::round(mapBG.getWidth() * scale);
		double scale2 = double(edit_area.get().w) / double(scaled_w);

		mapBG_area.setW(std::round(mapBG.getWidth() * scale2));

		if (mapBG_area.get().w > mapBG.getWidth())
			mapBG_area.setW(mapBG.getWidth());*/

		int scaled_w = std::round(mapBG.getWidth() * scale);
		double scale2 = double(edit_area.get().w) / double(scaled_w);

		mapBG_area.setW(std::round(mapBG.getWidth() * scale2));

		if (mapBG_area.get().w > mapBG.getWidth())
			mapBG_area.setW(mapBG.getWidth());
	}
	else
		mapBG_area.setW(scale * mapBG.getWidth());

	Map_manager::update_mapBG(mapBG_area.get().w, mapBG_area.get().h);

	Init_objectsSize();

	Engine_manager::set_updateState(Engine_updateState::RENDER_READY);
}

void Map::mouse_handler()
{
	static const int & mX = Mouse::getX();
	static const int & mY = Mouse::getY();

	mouse_over = false;

	if (Mouse::getX() >= edit_area.left() && Mouse::getX() <= edit_area.right()
		&& Mouse::getY() >= edit_area.up() && Mouse::getY() <= edit_area.down())
	{
		mouse_over = true;
		if (Mouse::getBt_state() == Mouse_key::L_BUTTON) { // pojedyncze klikniêcie
			switch (Map_manager::getMain_state())
			{
			case Map_state::PLACING_OBJECTS:
				placing_mouseL_Events(); // zdarzenia dla klikniêcia lewego przycisku myszy
				break;
			case Map_state::MOVING_OBJECT:
				movingObject_mouseL_event();
				break;
			case Map_state::SELECTING_OBJECTS:
				switch (Map_manager::getSelect_satate()) {
				case Selecting_Obj_state::MULTI:
					multiOBJ_s.reset(edit_area.get());
					break;
				}
				break;
			}
		}

		if (Mouse::is_pressedL()) { // przytrzymanie lewego klawisza myszy
			switch (Map_manager::getMain_state()) {
			case Map_state::MOVING_MAP:
				move_map_Mouse();
				break;
			case Map_state::SELECTING_OBJECTS:
				switch (Map_manager::getSelect_satate()) {
				case Selecting_Obj_state::MULTI:
					pressing_mouseL_multiOBJ_select = true;
					multi_selectingObject_mouseEvents();
					break;
				}

				break;
			}
		}
		else
		{
			switch (Map_manager::getMain_state()) {
			case Map_state::SELECTING_OBJECTS:
				switch (Map_manager::getSelect_satate()) {
				case Selecting_Obj_state::MULTI:
					if (pressing_mouseL_multiOBJ_select)
					{
						Map_manager::setMain_state(Map_state::SELECTING_OBJECTS_FINISHED);
						pressing_mouseL_multiOBJ_select = false;
					}
					break;
				}

				break;
			}
		}
		if (Mouse::getBt_state() == Mouse_key::R_BUTTON) {
			switch (Map_manager::getMain_state()) {
			case Map_state::PLACING_OBJECTS:
				Map_manager::switch_OBJ_orient();
				break;
			case Map_state::MOVING_OBJECT:
				singleOBJmove_s.current_enemy->switch_orient();
				break;
			case Map_state::SELECTING_OBJECTS:
				if (Map_manager::getSelect_satate() == Selecting_Obj_state::MULTI)
					multi_selecingOBJ_mouseR();
				break;
			case Map_state::MULTI_MOVING_OBJECTS:
				multi_movingObject_mouseR_event();
				break;
			}
		}
		if (Mouse::getWheelState() != Mouse_wheel::NONE)
			move_map_Wheel();
	}
}

void Map::Init_objectsSize() // uruchamiane po wczytaniu mapy
{
	using namespace Enemy_Types;

	// Inicjacja danych, które uwa¿ana s¹ za sta³e i niezmienne (nie mog¹ byæ const bo musialyby byæ zadeklarowane od razu, a takim sposobem deklarowane s¹ po za³adowaniu mapy i przustosowuj¹ siê do niej)
	Enemy_Test::Init_renderSize();
	Enemy_Test2::Init_renderSize();
	Enemy_Test3::Init_renderSize();
	Enemy_Test4::Init_renderSize();
}

void Map::update_events()
{
	switch (Map_manager::get_Update_state()) { // zdarzenia, które maja zaktualizowaæ dane raz na jaki czas(nie ca³y czas, bo zmniejszy³oby to wydajnoœæ)
	case Map_Update_state::UPDATED_OBJECTS_SIZE:
		for (auto & enemy : enemies)
			enemy->update_Size();
		break;
	case Map_Update_state::MODULE_CHANGED:
		switch (Map_manager::get_currentModule()) {
		case Current_MapModule::BLOCK_PLACER:
			break;
		case Current_MapModule::ENEMIES_PLACER:
			break;
		}
	}
	Map_manager::reset_UpdateState();
}

void Map::reset()
{
	enemies.clear();
	multiOBJ_s.reset(edit_area.get());
	Map_manager::reset();
}

void Map::multi_selectingObject_events()
{
	/*for (auto & enemy : enemies) {
	auto & pos = enemy->get_renderPOS();
	if (pos.x > multiOBJ_s.area.x && pos.y > multiOBJ_s.area.y
	&& pos.x + pos.w < multiOBJ_s.area.x + multiOBJ_s.area.w && pos.y + pos.h < multiOBJ_s.area.y + multiOBJ_s.area.h)
	{
	multiOBJ_s.set_borderOBJ(pos, enemy.get());
	enemy->set_selectState(true);
	}
	else
	enemy->set_selectState(false);
	}*/

	const Uint8 * keyboard = SDL_GetKeyboardState(nullptr);

	if (keyboard[SDL_SCANCODE_DELETE]) {
		multiOBJ_s.reset(edit_area.get());
		for (int i = 0; i != enemies.size(); i++) {
			if (enemies[i]->is_selected()) {
				std::swap(enemies[i], enemies.back());
				enemies.pop_back();
				i--;
			}
		}
	}
}

void Map::placing_mouseL_Events()
{
	auto & tmp_pos = Map_manager::get_tempRender_area();

	static double scaleTX_w, scaleTX_h;
	static int x, y;
	scaleTX_w = double(tmp_pos.x - edit_area.get().x) / edit_area.get().w;
	scaleTX_h = double(tmp_pos.y - edit_area.get().y) / edit_area.get().h;
	x = mapBG_area.get().x + round(mapBG_area.get().w * scaleTX_w);
	y = mapBG_area.get().y + round(mapBG_area.get().h * scaleTX_h);


	static int RenderPOS_X, RenderPOS_Y;
	static double scaleX, scaleY;
	scaleX = double(x - mapBG_area.get().x) / double(mapBG_area.get().w);
	scaleY = double(y - mapBG_area.get().y) / double(mapBG_area.get().h);
	RenderPOS_X = round(scaleX * edit_area.get().w) + edit_area.get().x;
	RenderPOS_Y = round(scaleY * edit_area.get().h) + edit_area.get().y;

	current_module->placing_object_events(x, y, RenderPOS_X, RenderPOS_Y);

	/*switch (Map_manager::get_OBJ_type())
	{
	case OBJ_type::ENEMY:
	create_EnemyOBJ(x, y, Map_manager::get_EnemyID(), Map_manager::get_OBJ_orient()); // przy dzia³aniu programu i przy ³adowaniu z pliku
	break;
	}*/
}

void Map::create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip)
{
	using namespace Enemy_Types;

	static int RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H;
	static double scaleX, scaleY;

	scaleX = double(X - mapBG_area.get().x) / double(mapBG_area.get().w);
	scaleY = double(Y - mapBG_area.get().y) / double(mapBG_area.get().h);

	RenderPOS_X = round(scaleX * edit_area.get().w) + edit_area.get().x;
	RenderPOS_Y = round(scaleY * edit_area.get().h) + edit_area.get().y;

	switch (id)
	{
	case Enemy_ID::TEST:
		enemies.push_back(Enemy_ptr{ new Enemy_Test{ X, Y, flip } });
		break;
	case Enemy_ID::TEST2:
		enemies.push_back(Enemy_ptr{ new Enemy_Test2{ X, Y, flip } });
		break;
	case Enemy_ID::TEST3:
		enemies.push_back(Enemy_ptr{ new Enemy_Test3{ X, Y, flip } });
		break;
	case Enemy_ID::TEST4:
		enemies.push_back(Enemy_ptr{ new Enemy_Test4{ X, Y, flip } });
		break;
	}
	enemies.back()->set_renderPOS(RenderPOS_X, RenderPOS_Y, Map_manager::get_tempRenderW(), Map_manager::get_tempRenderH());
}

void Map::create_EnemyOBJ(const SDL_Rect & mapPOS, const Enemy_ID & id, const SDL_RendererFlip & flip)
{
	using namespace Enemy_Types;

	static int RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H;
	static double scaleX, scaleY;

	scaleX = double(mapPOS.x - mapBG_area.get().x) / double(mapBG_area.get().w);
	scaleY = double(mapPOS.y - mapBG_area.get().y) / double(mapBG_area.get().h);

	RenderPOS_X = round(scaleX * edit_area.get().w) + edit_area.get().x;
	RenderPOS_Y = round(scaleY * edit_area.get().h) + edit_area.get().y;

	switch (id)
	{
	case Enemy_ID::TEST:
		enemies.push_back(Enemy_ptr{ new Enemy_Test{ mapPOS, flip } });
		break;
	case Enemy_ID::TEST2:
		enemies.push_back(Enemy_ptr{ new Enemy_Test2{ mapPOS, flip } });
		break;
	case Enemy_ID::TEST3:
		enemies.push_back(Enemy_ptr{ new Enemy_Test3{ mapPOS, flip } });
		break;
	case Enemy_ID::TEST4:
		enemies.push_back(Enemy_ptr{ new Enemy_Test4{ mapPOS, flip } });
		break;
	}

	scaleX = double(mapPOS.w) / double(mapBG_area.get().w);
	scaleY = double(mapPOS.h) / double(mapBG_area.get().h);

	RenderPOS_W = round(scaleX * edit_area.get().w);
	RenderPOS_H = round(scaleY * edit_area.get().h);

	enemies.back()->set_renderPOS(RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H);
}

void Map::events_enemies()
{
	for (auto & enemy : enemies)
		enemy->events();
}

void Map::events_delete_enemies()
{
	for (auto & enemy : enemies)
	{
		enemy->events();
		if (enemy->is_clicked())
			break;
	}
}

void Map::render_map()
{
	mapBG.render(&mapBG_area.get(), &edit_area.get());

	SDL_SetRenderDrawColor(Renderer::get(), 120, 120, 120, 255);
	SDL_RenderDrawRect(Renderer::get(), &edit_area.get());
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}

void Map::render_enemies()
{
	static SDL_Rect temp_pos, texture_area;

	for (auto & enemy : enemies) {
		//auto & pos = enemy->get_renderPOS();
		auto& pos_temp = enemy->get_renderPOS();
		Rect pos;
		pos.set(pos_temp);

		if (pos.left() >= edit_area.left() && pos.right() <= edit_area.right())
			enemy->render(); // renderuj ca³y obiekt
		else if (pos.left() < edit_area.left() && pos.right() > edit_area.left()) {
			temp_pos = { edit_area.left() , pos.get().y, pos.right() - edit_area.left(), pos.get().h };

			auto & tX = enemy->getTX();

			double scale = double(temp_pos.w) / double(pos.get().w);

			texture_area.x = tX.getWidth() - std::round(tX.getWidth() * scale);
			texture_area.y = 0;
			texture_area.w = tX.getWidth() - texture_area.x;
			texture_area.h = tX.getHeight();

			if (enemy->is_flipped()) {
				texture_area.w = tX.getWidth() - texture_area.x;
				texture_area.x = 0;
			}

			enemy->render(texture_area, temp_pos);
		}
		else if (pos.right() > edit_area.right() && pos.left() <= edit_area.right()) {
			temp_pos = { pos.get().x, pos.get().y, edit_area.right() - pos.left(), pos.get().h };

			auto & tX = enemy->getTX();

			double scale = double(temp_pos.w) / double(pos.get().w);

			texture_area.x = 0;
			texture_area.y = 0;
			texture_area.w = std::round(tX.getWidth() * scale);
			texture_area.h = tX.getHeight();

			if (enemy->is_flipped()) {
				texture_area.x = tX.getWidth() - texture_area.w;
				texture_area.w = tX.getWidth() - texture_area.x;
			}

			enemy->render(texture_area, temp_pos);
		}
	}
}

void Map::multi_selectingObject_mouseEvents()
{
	static const int & mX = Mouse::getX();
	static const int & mY = Mouse::getY();

	const SDL_Point & point = Mouse::get_clickedPoint();

	if (mouse_over) {

		if (mX < point.x)
		{
			multiOBJ_s.setX(mX);
			multiOBJ_s.setW(point.x - mX);
		}
		else {
			multiOBJ_s.setX(point.x);
			multiOBJ_s.setW(mX - point.x);
		}
		if (mY < point.y) {
			multiOBJ_s.setY(mY);
			multiOBJ_s.setH(point.y - mY);
		}
		else {
			multiOBJ_s.setY(point.y);
			multiOBJ_s.setH(mY - point.y);
		}
	}
}

void Map::multi_selecingOBJ_mouseR()
{
	if (Mouse::is_inPOS(multiOBJ_s.get()))
	{
		multiOBJ_s.updateOBJs(Mouse::get_clickedPoint());
		Map_manager::setMain_state(Map_state::MULTI_MOVING_OBJECTS);
	}
}

void Map::single_selectingObject_events()
{
	for (auto & enemy : enemies) {
		if (enemy->is_clicked()) {
			if (!enemy->is_selected())
			{
				enemy->switch_selected_state();

				singleOBJmove_s.set(enemy.get());

				Map_manager::setMain_state(Map_state::MOVING_OBJECT);
			}
			else
				enemy->switch_selected_state();
			break;
		}
	}
}

void Map::deleting_objects_events()
{
	for (auto & enemy : enemies) {
		if (enemy->is_clicked()) {
			std::swap(enemy, enemies.back());
			enemies.pop_back();
			break;
		}
	}
}

void Map::movingObject_mouseL_event()
{
	double scaleTX_w, scaleTX_h;
	int x, y;

	scaleTX_w = double(singleOBJmove_s.current_enemy->get_renderPOS().x - edit_area.get().x) / edit_area.get().w;
	scaleTX_h = double(singleOBJmove_s.current_enemy->get_renderPOS().y - edit_area.get().y) / edit_area.get().h;

	x = mapBG_area.get().x + round(mapBG_area.get().w * scaleTX_w);
	y = mapBG_area.get().y + round(mapBG_area.get().h * scaleTX_h);

	int RenderPOS_X, RenderPOS_Y;
	double scaleX, scaleY;
	scaleX = double(x - mapBG_area.get().x) / double(mapBG_area.get().w);
	scaleY = double(y - mapBG_area.get().y) / double(mapBG_area.get().h);
	RenderPOS_X = round(scaleX * edit_area.get().w) + edit_area.get().x;
	RenderPOS_Y = round(scaleY * edit_area.get().h) + edit_area.get().y;

	singleOBJmove_s.current_enemy->update_mapPOS(x, y);
	singleOBJmove_s.current_enemy->update_renderPOS(RenderPOS_X, RenderPOS_Y);

	singleOBJmove_s.reset();

	Map_manager::setMain_state(Map_state::SELECTING_OBJECTS);
}

void Map::multi_movingObject_mouseR_event()
{
	for (auto& enemy : multiOBJ_s.moving_objects) {

		double scaleTX_w, scaleTX_h;
		int x, y;

		scaleTX_w = double(enemy.enemy->get_renderPOS().x - edit_area.get().x) / edit_area.get().w;
		scaleTX_h = double(enemy.enemy->get_renderPOS().y - edit_area.get().y) / edit_area.get().h;

		x = mapBG_area.get().x + round(mapBG_area.get().w * scaleTX_w);
		y = mapBG_area.get().y + round(mapBG_area.get().h * scaleTX_h);

		int RenderPOS_X, RenderPOS_Y;
		double scaleX, scaleY;
		scaleX = double(x - mapBG_area.get().x) / double(mapBG_area.get().w);
		scaleY = double(y - mapBG_area.get().y) / double(mapBG_area.get().h);
		RenderPOS_X = round(scaleX * edit_area.get().w) + edit_area.get().x;
		RenderPOS_Y = round(scaleY * edit_area.get().h) + edit_area.get().y;

		enemy.enemy->update_mapPOS(x, y);
		enemy.enemy->update_renderPOS(RenderPOS_X, RenderPOS_Y);
	}

	Map_manager::setMain_state(Map_state::SELECTING_OBJECTS);
}

void Map::multiMoving_objects_events() // zdarzenia po nacisnieciu prawym klawiszem myszy na obszar zaznaczony do przeniesienia
{
	multiOBJ_s.events_moving(mouse_over, edit_area.get());
}

void Map::multiSelect_OBJs_set()
{
	for (auto & enemy : enemies) {
		auto & pos_temp = enemy->get_renderPOS();

		Rect pos;
		pos.set(pos_temp);

		if (pos.left() > multiOBJ_s.left() && pos.up() > multiOBJ_s.up()
			&& pos.right() < multiOBJ_s.right() && pos.down() < multiOBJ_s.down())
		{
			multiOBJ_s.set_borderOBJ(pos, enemy.get()); // ustaw obiekt graniczny i dodaj do obiektow przesuwanych
			enemy->set_selectState(true);
		}
		else
			enemy->set_selectState(false);
	}

	if (multiOBJ_s.moving_objects.size() == 0)
		multiOBJ_s.reset(edit_area.get());

	Map_manager::setMain_state(Map_state::SELECTING_OBJECTS);
}

void Map::move_map_Wheel()
{
	if (Mouse::getWheelState() == Mouse_wheel::UP && mapBG_area.right() < mapBG.getWidth()) {
		if (mapBG_area.right() + MAP_MOVE_SIZE <= mapBG.getWidth())
			mapBG_area.updateX(MAP_MOVE_SIZE);
		else
			mapBG_area.setX(mapBG.getWidth() - mapBG_area.get().w);
	}
	else if (Mouse::getWheelState() == Mouse_wheel::DOWN && mapBG_area.get().x >= 0) {

		if (mapBG_area.get().x - MAP_MOVE_SIZE > 0)
			mapBG_area.updateX(-MAP_MOVE_SIZE);
		else
			mapBG_area.setX(0);
	}

	static int RenderPOS_X, RenderPOS_Y;
	static double scaleX, scaleY;

	for (auto & enemy : enemies) {
		scaleX = double(enemy->get_mapX() - mapBG_area.get().x) / double(mapBG_area.get().w);
		scaleY = double(enemy->get_mapY() - mapBG_area.get().y) / double(mapBG_area.get().h);

		RenderPOS_X = round(scaleX * edit_area.get().w) + edit_area.get().x;
		RenderPOS_Y = round(scaleY * edit_area.get().h) + edit_area.get().y;

		enemy->update_renderPOS(RenderPOS_X, RenderPOS_Y);
	}
}

void Map::update_OBJs_renderPOS()
{
	for (auto & enemy : enemies) {
		static int RenderPOS_X, RenderPOS_Y;
		static double scaleX, scaleY;

		scaleX = double(enemy->get_mapX() - mapBG_area.get().x) / double(mapBG_area.get().w);
		scaleY = double(enemy->get_mapY() - mapBG_area.get().y) / double(mapBG_area.get().h);

		RenderPOS_X = round(scaleX * edit_area.get().w) + edit_area.get().x;
		RenderPOS_Y = round(scaleY * edit_area.get().h) + edit_area.get().y;

		enemy->update_renderPOS(RenderPOS_X, RenderPOS_Y);
	}
}

void Map::move_map_Mouse()
{
	static double scaleX, scale_recentX;
	static double scaleY, scale_recentY;

	static int pointX, point_recentX;

	static int maprender_absX, maprender_absY;

	//if (Mouse::getX() < Mouse::getR_x() || Mouse::getX() > Mouse::getR_x()
	//|| Mouse::getY() < Mouse::getR_y() || Mouse::getY() > Mouse::getY())

	if (Mouse::getX() != Mouse::getR_x() || Mouse::getY() != Mouse::getR_y())
	{
		scaleX = double(Mouse::getX() - edit_area.get().x) / double(edit_area.get().w);
		scale_recentX = double(Mouse::getR_x() - edit_area.get().x) / double(edit_area.get().w);

		pointX = mapBG_area.get().x + round(mapBG_area.get().w * scaleX);
		point_recentX = mapBG_area.get().x + round(mapBG_area.get().w * scale_recentX);

		maprender_absX = abs(pointX - point_recentX);

		if (Mouse::getX() < Mouse::getR_x() && mapBG_area.right() < mapBG.getWidth()) {
			if (mapBG_area.right() + maprender_absX < mapBG.getWidth())
				mapBG_area.update(maprender_absX, 0);
			else
				mapBG_area.setX(mapBG.getWidth() - mapBG_area.get().w);
		}
		else if (Mouse::getX() > Mouse::getR_x() && mapBG_area.get().x > 0) {

			if (mapBG_area.get().x - maprender_absX > 0)
				mapBG_area.updateX(-maprender_absX);
			else
				mapBG_area.setX(0);
		}

		for (auto & enemy : enemies) {
			static int RenderPOS_X, RenderPOS_Y;

			scaleX = double(enemy->get_mapX() - mapBG_area.get().x) / double(mapBG_area.get().w);
			scaleY = double(enemy->get_mapY() - mapBG_area.get().y) / double(mapBG_area.get().h);

			RenderPOS_X = round(scaleX * edit_area.get().w) + edit_area.get().x;
			RenderPOS_Y = round(scaleY * edit_area.get().h) + edit_area.get().y;

			enemy->update_renderPOS(RenderPOS_X, RenderPOS_Y);
		}
	}
}

void multiOBJ_select_structure::set_borderOBJ(const Rect & pos, Enemy * enemy)
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
		if (pos.right() > enemy_right->right()/*get_renderPOS().right()*/)
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

void multiOBJ_select_structure::render(const SDL_Rect & edit_a)
{
	SDL_Rect tmp = get();
	
	//Rect tmp{ area };

	Rect edit_area{ edit_a };

	Renderer::set_renderColor({ 0, 0, 255, 255 });

	if (get().x < edit_area.get().x) {
		tmp.x = edit_area.get().x;
		tmp.w -= edit_area.get().x - get().x;
	}
	if (get().y < edit_area.get().y) {
		tmp.y = edit_area.get().y;
		tmp.h -= edit_area.get().y - get().y;
	}
	if (right() > edit_area.right())
		tmp.w = edit_area.right() - left();
	if (down() > edit_area.down())
		tmp.h = edit_area.down() - up();

	SDL_RenderDrawRect(Renderer::get(), &tmp);
	Renderer::set_defaultColor();
}

void multiOBJ_select_structure::render()
{
	Renderer::set_renderColor({ 0, 0, 255, 255 });
	SDL_RenderDrawRect(Renderer::get(), &get());
	Renderer::set_defaultColor();
}

void multiOBJ_select_structure::events_moving(bool mouse_over, const SDL_Rect & edit_a)
{
	Rect edit_area{ edit_a };

	int tmp_px_left, tmp_px_up;

	setX(Mouse::getX() - px_left);
	setY(Mouse::getY() - px_up);

	tmp_px_left = tmp_px_up = 0;

	// nie wiem o co kaman ale cos zmienia pozycje renderowania i musi byæ najpierw ta pêtla
	for (auto & enemy : moving_objects)
		enemy.enemy->update_renderPOS(Mouse::getX() - enemy.px_left, Mouse::getY() - enemy.px_up);

	if (mouse_over) {

		if (enemy_up->up() < edit_area.up())
			tmp_px_up = edit_area.get().y - enemy_up->get_renderPOS().y;

		else if (enemy_down->down() > edit_area.down())
			tmp_px_up = edit_area.down() - enemy_down->down();

		if (enemy_left->get_renderPOS().x < edit_area.get().x)
			tmp_px_left = edit_area.get().x - enemy_left->get_renderPOS().x;

		else if (enemy_right->right() > edit_area.right())
			tmp_px_left = edit_area.right() - enemy_right->right();

		updateX(tmp_px_left);
		updateY(tmp_px_up);

		for (auto & enemy : moving_objects)
			enemy.enemy->update_about(tmp_px_left, tmp_px_up);
	}
}

void multiOBJ_select_structure::updateOBJs(SDL_Point clicked_point)
{
	// zachowanie proporcji po kliknieciu
	px_up = clicked_point.y - get().y; // ile px w gore potrzeba by zaznaczenie bylo w oryginalnej pozycji
	px_left = clicked_point.x - get().x;

	for (auto & enemy : moving_objects)
	{
		enemy.px_left = clicked_point.x - enemy.enemy->get_renderPOS().x;
		enemy.px_up = clicked_point.y - enemy.enemy->get_renderPOS().y;
	}
}

void singleOBJmove_structure::set(Enemy * enemy)
{
	current_enemy = enemy;

	px_left = Mouse::getX() - enemy->get_renderPOS().x;
	px_up = Mouse::getY() - enemy->get_renderPOS().y;
}

void singleOBJmove_structure::events(bool mouse_over, SDL_Rect edit_a)
{
	Rect edit_area{ edit_a };

	int tmp_px_left, tmp_px_up;

	tmp_px_left = tmp_px_up = 0;

	current_enemy->update_renderPOS(Mouse::getX() - px_left, Mouse::getY() - px_up);

	const Rect pos = Rect{ current_enemy->get_renderPOS() };

	if (mouse_over)
	{
		if (pos.get().y < edit_area.get().y)
			tmp_px_up = edit_area.get().y - current_enemy->get_renderPOS().y;

		else if (pos.down() > edit_area.down())
			tmp_px_up = edit_area.down() - pos.down();

		if (pos.get().x < edit_area.get().x)
			tmp_px_left = edit_area.get().x - pos.get().x;

		else if (pos.right() > edit_area.right())
			tmp_px_left = edit_area.right() - pos.right();

		current_enemy->update_about(tmp_px_left, tmp_px_up);
	}
}