#pragma once
#include <string>
#include <SDL_rect.h>
#include <vector>
#include "Enemy_OBJ.h"
#include "Block_OBJ.h"
#include <fstream>
#include "Texture.h"
#include "Button_Placing_EnemyOBJ.h"
#include "Coordinates_bar.h"
#include "Menu_localEditor.h"

class LevelCreator
{
	struct Map_area {
		bool canMove_r(const Texture & TX);
		bool canMove_l();
		bool canMove_u();
		bool canMove_d(const Texture & TX);

		SDL_Rect area;
	};
public:
	LevelCreator();

	void events();
	void events_indp();
	void render();
private:
	void load_Level();
	void new_Level();

	void save_level();

	void mouse_handler();

	void set_PlayerSpawn();
	void create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);

	void clear_map();

	bool editArea_isMouseOver();

	void setMap_view();
	void setMap_viewWheel_scroll();

	void render_Map();
	void render_Enemies();
	void render_Blocks();

	void events_enemies();
	void events_blocks();

	void placingObjects_events();
	void movingMap_events();
	void selecingObjects_events();
	void deletingObjects_events();
	void movingOBJ_events();

	void setMap_area();

	void switch_enemiesTypes(const int & mX, const int & mY);
	void switch_blockTypes(const int & mX, const int & mY);
	void switch_othersTypes(const int & mX, const int & mY);

	void set_tempEnemySize();
	void set_tempBlockSize();
	void set_tempOtherSize();

	void set_tempPlacing_OBJ_pos();
private:
	std::vector<Enemy_OBJ*> enemies;
	std::vector<Block_OBJ*> blocks;

	Button_Placing_EnemyOBJ button_enemyPlace_test;

	Menu_localEditor localMenu_bar; // lokalne menu - przyciski LEVEL, OBJECTS itd. zawieraj� 

	Enemy_data enemy_data;
	Block_data block_data;

	SDL_Rect edit_area;

	Map_area mapBG_area;

	std::ofstream save;
	std::ifstream load;

	Texture mapBG;

	bool l_buttonPressing; // Czy klikni�ty lewy przycisk przynajmniej raz? Je�eli tak = true, w przeciwnym wypadku czekaj a� nie b�dzie naci�niety i = false.

	static const int MAP_MOVE_SIZE = 20; // ilo�� pixeli przesuni�cia mapy

	SDL_Rect temp_objPOS;

	Coordinates_bar map_coordinate;
	Coordinates_bar mouse_cord;
};