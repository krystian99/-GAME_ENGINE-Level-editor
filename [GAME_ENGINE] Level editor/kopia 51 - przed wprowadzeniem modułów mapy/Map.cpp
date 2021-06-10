#include "Map.h"
#include "LevelEditor_manager.h"
#include "Video_Info.h"
#include "Mouse.h"
#include "Map_manager.h"
#include "Renderer.h"
#include "Enemy_Types.h"

Map::Map(const SDL_Rect & pos) : 
	blockPlacer_module{ blocks }
{
	edit_area = pos;
	Video_Info::set_scaledSize(edit_area);

	Map_manager::set_edit_area(edit_area.w, edit_area.h);
}

void Map::save_Objects(const std::string & name)
{
	using std::ios_base;

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
	case Map_state::PLACING_OBJECTS:
		if (current_enemy)
			current_enemy->update_renderPOS(Mouse::getX(), Mouse::getY()); // przed tym trzeba zapisaæ kopiê wczesniejszej pozycji
		break;
	}
}

void Map::render()
{
	render_map();
	render_enemies();

	switch (Map_manager::getMain_state()) {
	case Map_state::PLACING_OBJECTS:
		if (!current_enemy)
			Map_manager::render_tempOBJ();
		else
			current_enemy->render();
		break;
	case Map_state::SELECTING_OBJECTS:
		switch (Map_manager::getSelect_satate()) {
		case Selecting_Obj_state::MULTI:
			Renderer::set_renderColor({ 0, 0, 255, 255 });
			SDL_RenderDrawRect(Renderer::get(), &multi_selecting_area);
			Renderer::set_defaultColor();
			break;
		}
		break;
	}
}

void Map::set_background(const std::string & bg)
{
	Map_manager::set_Background_name(bg);

	mapBG.loadFromFile(bg);

	mapBG_area.x = 0;
	mapBG_area.y = 0;
	mapBG_area.h = mapBG.getHeight();

	double scale = double(edit_area.h) / double(mapBG.getHeight());

	if (mapBG.getHeight() < edit_area.h)
	{
		int scaled_w = std::round(mapBG.getWidth() * scale);
		double scale2 = double(edit_area.w) / double(scaled_w);

		mapBG_area.w = std::round(mapBG.getWidth() * scale2);

		if (mapBG_area.w > mapBG.getWidth())
			mapBG_area.w = mapBG.getWidth();
	}
	else {
		mapBG_area.w = std::round(scale * mapBG.getWidth());
	}

	Map_manager::update_mapBG(mapBG_area.w, mapBG_area.h);

	Init_objectsSize();
}

void Map::mouse_handler()
{
	static const int & mX = Mouse::getX();
	static const int & mY = Mouse::getY();

	mouse_over = false;

	if (Mouse::getX() >= edit_area.x && Mouse::getX() <= edit_area.x + edit_area.w
		&& Mouse::getY() >= edit_area.y && Mouse::getY() <= edit_area.y + edit_area.h)
	{
		mouse_over = true;
		if (Mouse::getBt_state() == Mouse_key::L_BUTTON) { // pojedyncze klikniêcie
			switch (Map_manager::getMain_state())
			{
			case Map_state::PLACING_OBJECTS:
				placing_mouseL_Events(); // zdarzenia dla klikniêcia lewego przycisku myszy
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
					multi_selectingObject_mouseEvents();
					break;
				}

				break;
			}
		}
		else if (Mouse::getBt_state() == Mouse_key::R_BUTTON) {
			switch (Map_manager::getMain_state()) {
			case Map_state::PLACING_OBJECTS:
				placing_mouseR_Events();
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
	}
	Map_manager::reset_UpdateState();
}

void Map::update_ObjectsSize()
{

}

void Map::reset()
{
	enemies.clear();
	Map_manager::reset();
}

void Map::placing_objects_events()
{

}

void Map::multi_selectingObject_events()
{
	for (auto & enemy : enemies) {
		auto & pos = enemy->get_renderPOS();
		if (pos.x > multi_selecting_area.x && pos.y > multi_selecting_area.y
			&& pos.x + pos.w < multi_selecting_area.x + multi_selecting_area.w && pos.y + pos.h < multi_selecting_area.y + multi_selecting_area.h)
		{
			enemy->set_selectState(true);
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

void Map::placing_mouseL_Events()
{
	static double scaleTX_w, scaleTX_h;
	static int x, y;

	scaleTX_w = double(Mouse::getX() - edit_area.x) / edit_area.w;
	scaleTX_h = double(Mouse::getY() - edit_area.y) / edit_area.h;

	x = mapBG_area.x + round(mapBG_area.w * scaleTX_w);
	y = mapBG_area.y + round(mapBG_area.h * scaleTX_h);

	if (!current_enemy) {
		switch (Map_manager::get_OBJ_type())
		{
		case OBJ_type::ENEMY:
			create_EnemyOBJ(x, y, Map_manager::get_EnemyID(), Map_manager::get_OBJ_orient()); // przy dzia³aniu programu i przy ³adowaniu z pliku
			break;
		}
	}
	else {
		int RenderPOS_X = round(scaleTX_w * edit_area.w) + edit_area.x;
		int RenderPOS_Y = round(scaleTX_h * edit_area.h) + edit_area.y;

		current_enemy->update_mapPOS(x, y);
		current_enemy->update_renderPOS(RenderPOS_X, RenderPOS_Y);
		current_enemy = nullptr;
		Map_manager::switch_to_prev_state();
	}
}

void Map::placing_mouseR_Events()
{
	if (!current_enemy)
		Map_manager::switch_OBJ_orient();
	else
		current_enemy->switch_orient();
}

void Map::create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip)
{
	using namespace Enemy_Types;

	static int RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H;
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
		enemies.push_back(new Enemy_Test2{ X, Y, flip });
		break;
	case Enemy_ID::TEST3:
		enemies.push_back(new Enemy_Test3{ X, Y, flip });
		break;
	case Enemy_ID::TEST4:
		enemies.push_back(new Enemy_Test4{ X, Y, flip });
		break;
	}
	enemies.back()->set_renderPOS(RenderPOS_X, RenderPOS_Y, Map_manager::get_tempRenderW(), Map_manager::get_tempRenderH());
}

void Map::create_EnemyOBJ(const SDL_Rect & mapPOS, const Enemy_ID & id, const SDL_RendererFlip & flip)
{
	using namespace Enemy_Types;

	static int RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H;
	static double scaleX, scaleY;

	scaleX = double(mapPOS.x - mapBG_area.x) / double(mapBG_area.w);
	scaleY = double(mapPOS.y - mapBG_area.y) / double(mapBG_area.h);

	RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
	RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

	switch (id)
	{
	case Enemy_ID::TEST:
		enemies.push_back(new Enemy_Test{ mapPOS, flip });
		break;
	case Enemy_ID::TEST2:
		enemies.push_back(new Enemy_Test2{ mapPOS, flip });
		break;
	case Enemy_ID::TEST3:
		enemies.push_back(new Enemy_Test3{ mapPOS, flip });
		break;
	case Enemy_ID::TEST4:
		enemies.push_back(new Enemy_Test4{ mapPOS, flip });
		break;
	}

	scaleX = double(mapPOS.w) / double(mapBG_area.w);
	scaleY = double(mapPOS.h) / double(mapBG_area.h);

	RenderPOS_W = round(scaleX * edit_area.w);
	RenderPOS_H = round(scaleY * edit_area.h);

	enemies.back()->set_renderPOS(RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H);
}

void Map::events_enemies()
{
	for (auto & enemy : enemies)
		enemy->events();
}

void Map::events_delete_enemies()
{
	for (auto enemy : enemies)
	{
		enemy->events();
		if (enemy->is_clicked())
			break;
	}
}

void Map::render_map()
{
	mapBG.render(&mapBG_area, &edit_area);

	SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::get(), &edit_area);
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}

void Map::render_enemies()
{
	static SDL_Rect temp_pos, texture_area;

	for (auto & enemy : enemies) {
		auto & pos = enemy->get_renderPOS();
		if (pos.x >= edit_area.x && pos.x + pos.w <= edit_area.x + edit_area.w)
			enemy->render(); // renderuj ca³y obiekt
		else if (pos.x < edit_area.x && pos.x + pos.w > edit_area.x) {
			temp_pos = { edit_area.x, pos.y, pos.x + pos.w - edit_area.x, pos.h };

			auto & tX = enemy->getTX();

			double scale = double(temp_pos.w) / double(pos.w);

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
		else if (pos.x + pos.w > edit_area.x + edit_area.w && pos.x <= edit_area.x + edit_area.w) {
			temp_pos = { pos.x, pos.y, edit_area.x + edit_area.w - pos.x, pos.h };

			auto & tX = enemy->getTX();

			double scale = double(temp_pos.w) / double(pos.w);

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

	if (mX < Mouse::get_clickedPoint().x)
	{
		multi_selecting_area.x = mX;
		multi_selecting_area.w = Mouse::get_clickedPoint().x - mX;
	}
	else {
		multi_selecting_area.x = Mouse::get_clickedPoint().x;
		multi_selecting_area.w = mX - Mouse::get_clickedPoint().x;
	}
	if (mY < Mouse::get_clickedPoint().y) {
		multi_selecting_area.y = mY;
		multi_selecting_area.h = Mouse::get_clickedPoint().y - mY;
	}
	else {
		multi_selecting_area.y = Mouse::get_clickedPoint().y;
		multi_selecting_area.h = mY - Mouse::get_clickedPoint().y;
	}
}

void Map::single_selectingObject_events()
{
	for (auto & enemy : enemies) {
		if (enemy->is_clicked()) {
			if (!enemy->is_selected()) {
				current_enemy = enemy;
				enemy->switch_selected_state();
				Map_manager::setMain_state(Map_state::PLACING_OBJECTS);
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
	/*for (int i = 0; i != enemies.size(); i++) {
		if (enemies[i]->is_clicked()) {
			std::swap(enemies[i], enemies.back());
			enemies.pop_back();
			i--;
		}
	}*/
}

void Map::move_map_Wheel()
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

		enemy->update_renderPOS(RenderPOS_X, RenderPOS_Y);
	}
}

void Map::move_map_Mouse()
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

			enemy->update_renderPOS(RenderPOS_X, RenderPOS_Y);
		}
	}
}