#include "Map.h"
#include "LevelEditor_manager.h"
#include "Video_Info.h"
#include "Mouse.h"
#include "Map_manager.h"
#include "Renderer.h"
#include "Enemy_Types.h"
#include "Engine_manager.h"
#include "CoordinateBar_map.h"
#include "Event_handler.h"
#include "Event_handlerOBJ_map.h"
#include "EventOBJ.h"

Map::Map(int x, int y, int w, int h) :
	Object{ x, y, w, h },
	enemy_placerModule{ enemies, edit_area },
	multiOBJ_s{ enemies, edit_area, mapBG_area },
	deleteOBJ_s{ enemies },
	map_MOVE_mouse_s(enemies, mapBG_area, edit_area, mapBG),
	singleOBJmove_s{ enemies, edit_area, mapBG_area }
{
	Map_manager::INIT(&multiOBJ_s, &singleOBJmove_s, &deleteOBJ_s, &enemy_placerModule, &map_MOVE_mouse_s);

	edit_area.set_position(x, y, w, h);

	singleOBJmove_s.set_position(edit_area.get_position());
	map_MOVE_mouse_s.set_position(edit_area.get_position());
	deleteOBJ_s.set_position(edit_area.get_position());

	Map_manager::set_edit_area(edit_area.getW(), edit_area.getH());

	// ustaw pozycj� gdzie b�d� odbywa�y sie eventy na tej strukturze
	multiOBJ_s.set_position(edit_area.get_position());
}

void Map::save_Objects(const std::string& name)
{
	using std::ios_base;
	std::ofstream save;

	save.open(name.c_str(), ios_base::out | ios_base::binary);

	if (save.is_open()) {
		for (auto& enemy : enemies)
			save.write(reinterpret_cast<const char*>(&enemy->getData()), sizeof(enemy->getData()));
	}

	save.close();
}

void Map::load_Objects(const std::string& name)
{
	reset();

	using std::ios_base;
	std::ifstream load;

	Enemy_data enemy_data;

	set_background(LevelEditor_manager::get_levels_mapsPath() + LevelEditor_manager::get_backgroundName() + ".png");

	load.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName()).c_str(), ios_base::in | ios_base::binary);

	if (load.is_open()) {
		while (load.read(reinterpret_cast<char*>(&enemy_data), sizeof(Enemy_data)))
			create_EnemyOBJ(enemy_data.mapPOS, enemy_data.id, enemy_data.flip);
	}

	load.close();
}
//#include <iostream>
//using std::cout;

void Map::events() // zdarzenia zale�ne od myszki(przyciski myszki: lewy, prawy, k�ko)
{
	updated = false;
	mouse_over = false;

	Object::events();

	//events_enemies();

	if (is_mouseOver())
	{
		events_enemies();

		map_mouseHandler.events();
		mouse_over = true;

		if (Map_manager::get_currentModule())
			Map_manager::get_currentModule()->events();
	}

	//Event_handler::push(new Event_handlerOBJ_map{ this, Map_events::events_enemies });
}

void Map::events_indp()
{
	if (Map_manager::get_Update_state() != Map_Update_state::NONE)
		update_events();

	if (Map_manager::get_currentModule())
		Map_manager::get_currentModule()->events_indp();

}

void Map::set_cord(const CoordinateBar_mouse* mouse_cord)
{
	this->mouse_cord = mouse_cord;
}

void Map::render()
{
	render_map();
	render_enemies();

	//Event_handler::push(new EventOBJ<Map>{ this, Map_events::render_map }); // testowe renderowanie
	//Event_handler::push(new EventOBJ<Map>{ this, Map_events::render_enemies }); // testowe renderowanie
	
	if (Map_manager::get_currentModule())
		Map_manager::get_currentModule()->render();
}

void Map::set_background(const std::string& bg)
{
	Map_manager::set_Background_name(bg);

	mapBG.loadFromFile(bg);

	mapBG_area.set_position(0, 0, -1, mapBG.getHeight());

	double scale = double(edit_area.getH()) / double(mapBG.getHeight());

	if (mapBG.getHeight() < edit_area.getH())
	{
		int scaled_w = std::round(mapBG.getWidth() * scale);
		double scale2 = double(edit_area.getW()) / double(scaled_w);

		mapBG_area.setW(std::round(mapBG.getWidth() * scale2));

		if (mapBG_area.getW() > mapBG.getWidth())
			mapBG_area.setW(mapBG.getWidth());
	}
	else
		mapBG_area.setW(scale * mapBG.getWidth());

	Map_manager::update_mapBG(mapBG_area.getW(), mapBG_area.getH());

	Init_objectsSize();

	Engine_manager::set_updateState(Engine_updateState::RENDER_READY);
}

void Map::on_mouseR1hit()
{
	//cout << "Wcisnieto prawy przycisk myszy!\n";
}

void Map::on_mouseWheel_down_1hit()
{
	if (mapBG_area.left() > 0) {
		if (mapBG_area.left() - MAP_MOVE_SIZE >= 0)
			mapBG_area.updateX(-MAP_MOVE_SIZE);
		else
			mapBG_area.setX(0);

		update_enemiesPOS();
	}
}

void Map::on_mouseWheel_up_1hit()
{
	if (mapBG_area.right() < mapBG.getWidth()) {
		if (mapBG_area.right() + MAP_MOVE_SIZE <= mapBG.getWidth())
			mapBG_area.updateX(MAP_MOVE_SIZE);
		else
			mapBG_area.setX(mapBG.getWidth() - mapBG_area.getW());

		update_enemiesPOS();
	}
}

void Map::set_ScaledSize()
{
	SDL_Rect rt = edit_area.get_position();

	rt.x = std::round(Video_Info::get_scaleW() * rt.x);
	rt.y = std::round(Video_Info::get_scaleH() * rt.y);
	rt.w = std::round(Video_Info::get_scaleW() * rt.w);
	rt.h = std::round(Video_Info::get_scaleH() * rt.h);

	edit_area.set_position(rt);
}

void Map::Init_objectsSize() // uruchamiane po wczytaniu mapy
{
	using namespace Enemy_Types;

	// Inicjacja danych, kt�re uwa�ana s� za sta�e i niezmienne (nie mog� by� const bo musialyby by� zadeklarowane od razu, a takim sposobem deklarowane s� po za�adowaniu mapy i przustosowuj� si� do niej)
	Enemy_Test::Init_renderSize();
	Enemy_Test2::Init_renderSize();
	Enemy_Test3::Init_renderSize();
	Enemy_Test4::Init_renderSize();
}

void Map::update_events()
{
	switch (Map_manager::get_Update_state()) { // zdarzenia, kt�re maja zaktualizowa� dane raz na jaki czas(nie ca�y czas, bo zmniejszy�oby to wydajno��)
	case Map_Update_state::UPDATED_OBJECTS_SIZE:
		for (auto& enemy : enemies)
			enemy->update_Size();
		break;
	}

	Map_manager::reset_UpdateState();
}

void Map::update_enemiesPOS()
{
	for (auto& enemy : enemies)
		enemy->set_renderPOS(edit_area, mapBG_area);
}

void Map::reset()
{
	enemies.clear();
	multiOBJ_s.reset();
	Map_manager::reset();
}

void Map::placing_mouseL_Events()
{
	auto& tmp_pos = Map_manager::get_tempRender_area();

	static double scaleTX_w, scaleTX_h;
	static int x, y;
	scaleTX_w = double(tmp_pos.x - edit_area.left()) / edit_area.getW();
	scaleTX_h = double(tmp_pos.y - edit_area.up()) / edit_area.getH();
	x = mapBG_area.left() + round(mapBG_area.getW() * scaleTX_w);
	y = mapBG_area.up() + round(mapBG_area.getH() * scaleTX_h);


	static int RenderPOS_X, RenderPOS_Y;
	static double scaleX, scaleY;
	scaleX = double(x - mapBG_area.left()) / double(mapBG_area.getW());
	scaleY = double(y - mapBG_area.up()) / double(mapBG_area.getH());
	RenderPOS_X = round(scaleX * edit_area.getW()) + edit_area.left();
	RenderPOS_Y = round(scaleY * edit_area.getH()) + edit_area.up();

	current_module->placing_object_events(x, y, RenderPOS_X, RenderPOS_Y);
}

void Map::create_EnemyOBJ(const int& X, const int& Y, const Enemy_ID& id, const SDL_RendererFlip& flip)
{
	using namespace Enemy_Types;

	static int RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H;
	static double scaleX, scaleY;

	scaleX = double(X - mapBG_area.left()) / double(mapBG_area.getW());
	scaleY = double(Y - mapBG_area.up()) / double(mapBG_area.getH());

	RenderPOS_X = round(scaleX * edit_area.getW()) + edit_area.left();
	RenderPOS_Y = round(scaleY * edit_area.getH()) + edit_area.up();

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
	enemies.back()->set_position(RenderPOS_X, RenderPOS_Y, Map_manager::get_tempRenderW(), Map_manager::get_tempRenderH());
}

void Map::create_EnemyOBJ(const SDL_Rect& mapPOS, const Enemy_ID& id, const SDL_RendererFlip& flip)
{
	using namespace Enemy_Types;

	static int RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H;
	static double scaleX, scaleY;

	scaleX = double(mapPOS.x - mapBG_area.left()) / double(mapBG_area.getW());
	scaleY = double(mapPOS.y - mapBG_area.up()) / double(mapBG_area.getH());

	RenderPOS_X = round(scaleX * edit_area.getW()) + edit_area.left();
	RenderPOS_Y = round(scaleY * edit_area.getH()) + edit_area.up();

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

	scaleX = double(mapPOS.w) / double(mapBG_area.getW());
	scaleY = double(mapPOS.h) / double(mapBG_area.getH());

	RenderPOS_W = round(scaleX * edit_area.getW());
	RenderPOS_H = round(scaleY * edit_area.getH());

	enemies.back()->set_position(RenderPOS_X, RenderPOS_Y, RenderPOS_W, RenderPOS_H);
}

void Map::events_enemies()
{
	for (auto& enemy : enemies) {
		enemy->events();
	}
}

void Map::render_map()
{
	mapBG.render(&mapBG_area.get_position(), &edit_area.get_position());

	SDL_SetRenderDrawColor(Renderer::get(), 120, 120, 120, 255);
	SDL_RenderDrawRect(Renderer::get(), &edit_area.get_position());
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}

void Map::render_enemies()
{
	static SDL_Rect temp_pos, texture_area;

	for (auto& enemy : enemies) {
		auto& pos_temp = enemy->get_position();
		Rect pos;
		pos.set_position(pos_temp);

		if (pos.left() >= edit_area.left() && pos.right() <= edit_area.right())
			enemy->render(); // renderuj ca�y obiekt
		else if (pos.left() <= edit_area.left() && pos.right() >= edit_area.left()) {
			temp_pos = { edit_area.left() , pos.up(), pos.right() - edit_area.left(), pos.getH() };

			auto& tX = enemy->getTX();

			double scale = double(temp_pos.w) / double(pos.getW());

			texture_area.x = tX.getWidth() - std::round(tX.getWidth() * scale);
			texture_area.y = 0;
			texture_area.w = tX.getWidth() - texture_area.x;
			texture_area.h = tX.getHeight();

			if (enemy->is_flipped()) {
				//texture_area.w = tX.getWidth() - texture_area.x;
				texture_area.x = 0;
			}

			enemy->render(texture_area, temp_pos);
		}
		else if (pos.right() >= edit_area.right() && pos.left() <= edit_area.right()) {
			temp_pos = { pos.left(), pos.up(), edit_area.right() - pos.left(), pos.getH() };

			auto& tX = enemy->getTX();

			double scale = double(temp_pos.w) / double(pos.getW());

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
