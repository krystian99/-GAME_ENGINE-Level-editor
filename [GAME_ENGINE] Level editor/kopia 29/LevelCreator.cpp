#include "LevelCreator.h"
#include "Mouse.h"
#include "Video_Info.h"
#include "Enemy_Test.h"
#include "LevelEditor_manager.h"
#include "Renderer.h"
#include "Engine_manager.h"
#include "Menu_manager.h"

void LevelCreator::load_Level()
{
	using std::ios_base;

	clear_map();


	char nazwa[100]{};

	load.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".properties").c_str(), ios_base::in | ios_base::binary);
	load.read(nazwa, 100);
	load.close();
	LevelEditor_manager::set_backgroundName(nazwa);

	mapBG.loadFromFile(LevelEditor_manager::get_levels_mapsPath() + nazwa + ".png");

	setMap_area();

	load.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName()).c_str(), ios_base::in | ios_base::binary);

	if (load.is_open()) {
		while (load.read(reinterpret_cast<char*>(&enemy_data), sizeof(Enemy_data)))
			create_EnemyOBJ(enemy_data.mapX, enemy_data.mapY, enemy_data.id, enemy_data.flip);
	}
	load.close();
}

void LevelCreator::new_Level()
{
	clear_map();
	mapBG.loadFromFile(LevelEditor_manager::get_levels_mapsPath() +  LevelEditor_manager::get_backgroundName() + ".png");

	setMap_area();
}

LevelCreator::LevelCreator() :
	button_enemyPlace_test{ Enemy_ID::TEST, { 1000, 10, 50, 50 } },
	l_buttonPressing{ false },
	map_coordinate{ {500, 30, 100, 50 }, &edit_area, &mapBG_area.area },
	mouse_cord{ { 700, 30, 100, 50 } }
{
	edit_area.x = round(20 * Video_Info::get_scaleW());
	edit_area.y = round(100 * Video_Info::get_scaleH());
	edit_area.w = Video_Info::getWindow_W() - round(90 * Video_Info::get_scaleW());
	edit_area.h = Video_Info::getWindow_H() - round(120 * Video_Info::get_scaleH());
}

void LevelCreator::events()
{
	mouse_handler();

	if (editArea_isMouseOver())
		map_coordinate.events();
	mouse_cord.events();
	localMenu_bar.events();
	//map_coordinate.events();

	button_enemyPlace_test.events();

	switch (LevelEditor_manager::getState()) {
	case LevelEditor_state::PLACING_OBJECTS:
		placingObjects_events();
		break;
	}
}

void LevelCreator::events_indp()
{
	events_enemies();
	events_blocks();
	//localMenu_bar.events();

	switch (LevelEditor_manager::getState())
	{
	case LevelEditor_state::IS_IN_LOCAL_MENU:
		localMenu_bar.events();
		break;
	case LevelEditor_state::CREATE_NEW_LEVEL:
		new_Level();
		LevelEditor_manager::reset();
		localMenu_bar.reset();
		break;
	case LevelEditor_state::LOAD_LEVEL:
		load_Level();
		LevelEditor_manager::reset();
		localMenu_bar.reset();
		break;
	case LevelEditor_state::SAVE_CURRENT_LEVEL: // zapisz pod nazw¹ wprowadzon¹ poczas wpisywania nazwy na samym pocz¹tku
		save_level(); // zapisz pod nazw¹ któr¹ podawano przy ³adowaniu/tworzeniu levela
		LevelEditor_manager::switch_to_previousState(); // przywróæ poprzedni stan
		break;
	case LevelEditor_state::SAVE_AS: // Zapisz pod inn¹ nazw¹
		save_level();
		LevelEditor_manager::switch_to_previousState(); // przywróæ poprzedni stan
		break;
	case LevelEditor_state::MOVING_MAP:
		movingMap_events();
		break;
	case LevelEditor_state::SELECTING_OBJECTS:
		selecingObjects_events();
		break;
	case LevelEditor_state::SET_TEMP_OBJ:
		set_tempPlacing_OBJ_pos();
		LevelEditor_manager::setSate(LevelEditor_state::PLACING_OBJECTS);
		break;
	}
}

void LevelCreator::render()
{
	if (LevelEditor_manager::getState() != LevelEditor_state::CREATE_NEW_LEVEL && LevelEditor_manager::getState() != LevelEditor_state::LOAD_LEVEL) {
		button_enemyPlace_test.render();
		render_Map();
		render_Blocks();
		render_Enemies();
		map_coordinate.render();
		mouse_cord.render();
		localMenu_bar.render();
		switch (LevelEditor_manager::getState())
		{
		case LevelEditor_state::PLACING_OBJECTS:
			LevelEditor_manager::getCurrentTX()->render(nullptr, &temp_objPOS, LevelEditor_manager::getOBJ_orient());
			break;
		}
	}
}

void LevelCreator::save_level()
{
	using std::ios_base;

	save.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName()).c_str(), ios_base::out | ios_base::binary);

	if (save.is_open()) {
		for (auto & enemy : enemies)
			save.write(reinterpret_cast<const char*>(&enemy->getData()), sizeof(enemy->getData()));
	}
	save.close();

	save.open((LevelEditor_manager::get_levelsPath() + LevelEditor_manager::get_levelName() + ".properties").c_str(), ios_base::out | ios_base::binary);
	save.write(LevelEditor_manager::get_backgroundName().c_str(), LevelEditor_manager::get_backgroundName().size());//sizeof(LevelEditor_manager::get_levelName().c_str()));
	save.close();
}

void LevelCreator::mouse_handler()
{
	static int mX, mY;

	mX = Mouse::getX();
	mY = Mouse::getY();

	if (editArea_isMouseOver())
	{
		if (Mouse::is_pressedL()) // gdy ca³y czas przyciœniête
			setMap_view();

		if (Mouse::getBt_state() == Mouse_key::L_BUTTON){ // gdy przycisk klikniêty tylko raz
			switch (LevelEditor_manager::getState())
			{
			case LevelEditor_state::PLACING_OBJECTS:
				static double scaleTX_w, scaleTX_h;
				static int x, y;

				scaleTX_w = double(mX - edit_area.x) / edit_area.w;
				scaleTX_h = double(mY - edit_area.y) / edit_area.h;

				x = mapBG_area.area.x + round(mapBG_area.area.w * scaleTX_w);
				y = mapBG_area.area.y + round(mapBG_area.area.h * scaleTX_h);

				create_EnemyOBJ(x, y, LevelEditor_manager::getEnemy_ID(), LevelEditor_manager::getOBJ_orient()); // przy dzia³aniu programu i przy ³adowaniu z pliku
				break;
			}
		}
		if (Mouse::getBt_state() == Mouse_key::R_BUTTON)
		{
			switch (LevelEditor_manager::getState())
			{
			case LevelEditor_state::PLACING_OBJECTS:
				LevelEditor_manager::switch_objOrient();
				break;
			}
		}
		if (Mouse::getWheelState() != Mouse_wheel::NONE)
			setMap_viewWheel_scroll();
	}
}

void LevelCreator::set_PlayerSpawn()
{

}

void LevelCreator::create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip)
{
	static int RenderPOS_X, RenderPOS_Y;
	static double scaleX, scaleY;

	scaleX = double(X - mapBG_area.area.x) / double(mapBG_area.area.w);
	scaleY = double(Y - mapBG_area.area.y) / double(mapBG_area.area.h);

	RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
	RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

	switch (id)
	{
	case Enemy_ID::TEST:
		enemies.push_back(new Enemy_Test{ X, Y, flip });
		break;
	}
	enemies.back()->set_position(RenderPOS_X, RenderPOS_Y);
}

void LevelCreator::clear_map()
{
	enemies.clear();
	blocks.clear();
}

bool LevelCreator::editArea_isMouseOver()
{
	if (Mouse::getX() >= edit_area.x && Mouse::getX() <= edit_area.x + edit_area.w
		&& Mouse::getY() >= edit_area.y && Mouse::getY() <= edit_area.y + edit_area.h)
	{
		return true;
	}
	return false;
}

void LevelCreator::setMap_view()
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

		pointX = mapBG_area.area.x + round(mapBG_area.area.w * scaleX);
		point_recentX = mapBG_area.area.x + round(mapBG_area.area.w * scale_recentX);

		maprender_absX = abs(pointX - point_recentX);

		if (Mouse::getX() < Mouse::getR_x() && mapBG_area.canMove_r(mapBG)) {
			if (mapBG_area.area.x + maprender_absX + mapBG_area.area.w < mapBG.getWidth())
				mapBG_area.area.x += maprender_absX;
			else
				mapBG_area.area.x = mapBG.getWidth() - mapBG_area.area.w;
		}
		else if (Mouse::getX() > Mouse::getR_x() && mapBG_area.canMove_l()) {

			if (mapBG_area.area.x - maprender_absX > 0)
				mapBG_area.area.x -= maprender_absX;
			else
				mapBG_area.area.x = 0;
		}

		for (auto & enemy : enemies) {
			static int RenderPOS_X, RenderPOS_Y;

			scaleX = double(enemy->get_mapX() - mapBG_area.area.x) / double(mapBG_area.area.w);
			scaleY = double(enemy->get_mapY() - mapBG_area.area.y) / double(mapBG_area.area.h);

			RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
			RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

			enemy->set_position(RenderPOS_X, RenderPOS_Y);
		}
	}
}

void LevelCreator::setMap_viewWheel_scroll()
{
	if (Mouse::getWheelState() == Mouse_wheel::UP || Mouse::getWheelState() == Mouse_wheel::DOWN)
	{
		if (Mouse::getWheelState() == Mouse_wheel::UP && mapBG_area.canMove_r(mapBG)) {
			if (mapBG_area.area.x + MAP_MOVE_SIZE + mapBG_area.area.w < mapBG.getWidth())
				mapBG_area.area.x += MAP_MOVE_SIZE;
			else
				mapBG_area.area.x = mapBG.getWidth() - mapBG_area.area.w;
		}
		else if (Mouse::getWheelState() == Mouse_wheel::DOWN && mapBG_area.canMove_l()) {

			if (mapBG_area.area.x - MAP_MOVE_SIZE > 0)
				mapBG_area.area.x -= MAP_MOVE_SIZE;
			else
				mapBG_area.area.x = 0;
		}

		for (auto & enemy : enemies) {
			static int RenderPOS_X, RenderPOS_Y;
			static double scaleX, scaleY;

			scaleX = double(enemy->get_mapX() - mapBG_area.area.x) / double(mapBG_area.area.w);
			scaleY = double(enemy->get_mapY() - mapBG_area.area.y) / double(mapBG_area.area.h);

			RenderPOS_X = round(scaleX * edit_area.w) + edit_area.x;
			RenderPOS_Y = round(scaleY * edit_area.h) + edit_area.y;

			enemy->set_position(RenderPOS_X, RenderPOS_Y);
		}
	}
}

void LevelCreator::render_Map()
{
	mapBG.render(&mapBG_area.area, &edit_area);

	SDL_SetRenderDrawColor(Renderer::get(), 255, 0, 0, 255);
	SDL_RenderDrawRect(Renderer::get(), &edit_area);
	SDL_SetRenderDrawColor(Renderer::get(), 255, 255, 255, 255);
}

void LevelCreator::render_Enemies()
{
	for (auto & enemy : enemies) {
		if (enemy->get_mapX() >= mapBG_area.area.x && enemy->get_mapX() <= mapBG_area.area.x + mapBG_area.area.w
			&& enemy->get_mapY() >= mapBG_area.area.y && enemy->get_mapY() <= mapBG_area.area.y + mapBG_area.area.h) 
		{
			enemy->render();
		}
	}
}

void LevelCreator::render_Blocks()
{
	for (auto & block : blocks)
		block->render();
}

void LevelCreator::events_enemies()
{
	for (auto & enemy : enemies)
		enemy->events();
}

void LevelCreator::events_blocks()
{
	for (auto & block : blocks)
		block->events();
}

void LevelCreator::placingObjects_events()
{
	temp_objPOS.x = Mouse::getX();
	temp_objPOS.y = Mouse::getY();
}

void LevelCreator::movingMap_events()
{
}

void LevelCreator::selecingObjects_events()
{
}

void LevelCreator::deletingObjects_events()
{
}

void LevelCreator::movingOBJ_events()
{
}

void LevelCreator::setMap_area()
{
	mapBG_area.area.x = 0;
	mapBG_area.area.y = 0;

	double scale = double(mapBG.getHeight()) / double(Video_Info::getWindow_H());

	mapBG_area.area.w = round(mapBG.getWidth() * scale);
	mapBG_area.area.h = mapBG.getHeight();
}

void LevelCreator::switch_enemiesTypes(const int & mX, const int & mY)
{
	switch (LevelEditor_manager::getEnemy_ID())
	{
	case Enemy_ID::TEST:
		
		break;
	}
}

void LevelCreator::switch_blockTypes(const int & mX, const int & mY)
{
}

void LevelCreator::switch_othersTypes(const int & mX, const int & mY)
{
}

void LevelCreator::set_tempEnemySize()
{
	switch (LevelEditor_manager::getEnemy_ID())
	{
	case Enemy_ID::TEST:
		temp_objPOS.x = Mouse::getX();
		temp_objPOS.y = Mouse::getY();
		temp_objPOS.w = round(Enemy_Test::width * Video_Info::get_scaleW());
		temp_objPOS.h = round(Enemy_Test::height * Video_Info::get_scaleH());
		break;
	}
}

void LevelCreator::set_tempBlockSize()
{
}

void LevelCreator::set_tempOtherSize()
{
}

void LevelCreator::set_tempPlacing_OBJ_pos()
{
	switch (LevelEditor_manager::getType_OBJ())
	{
	case OBJ_TYPES::ENEMY:
		set_tempEnemySize();
		break;
	case OBJ_TYPES::BLOCK:
		set_tempBlockSize();
		break;
	case OBJ_TYPES::OTHERS:
		set_tempOtherSize();
		break;
	}
}

bool LevelCreator::Map_area::canMove_r(const Texture & TX)
{
	if (area.x + area.w < TX.getWidth())
		return true;
	return false;
}

bool LevelCreator::Map_area::canMove_l()
{
	if (area.x > 0)
		return true;
	return false;
}

bool LevelCreator::Map_area::canMove_u()
{
	if (area.y > 0)
		return true;
	return false;
}

bool LevelCreator::Map_area::canMove_d(const Texture & TX)
{
	if (area.y + area.h > TX.getHeight())
		return true;
	return false;
}