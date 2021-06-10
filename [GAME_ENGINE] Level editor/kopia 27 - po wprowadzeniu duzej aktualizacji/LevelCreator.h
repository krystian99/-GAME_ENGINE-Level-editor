#pragma once
#include <string>
#include <SDL_rect.h>
#include <vector>
#include "Enemy_OBJ.h"
#include "Block_OBJ.h"
#include <fstream>
#include "Texture.h"

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
	LevelCreator() {}

	void Init();

	void load_Level(const std::string & level_name);
	void new_Level(const std::string & level_name, const std::string & map_path);

	void events();
	void render();
private:
	void save_level();

	void mouse_handler();

	void set_PlayerSpawn();
	void create_EnemyOBJ(const int & X, const int & Y);

	void clear_map();

	void setMap_view();

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
private:
	SDL_Rect mapArea;

	std::vector<Enemy_OBJ> enemies;
	std::vector<Block_OBJ> blocks;

	Enemy_data enemy_data;
	Block_data block_data;

	SDL_Rect edit_area;

	Map_area mapBG_area;

	std::string level_name;

	std::ofstream save;
	std::ifstream load;

	Texture mapBG;
};