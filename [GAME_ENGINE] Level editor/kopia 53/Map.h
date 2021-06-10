#pragma once
#include <SDL_rect.h>
#include <fstream>
#include "Texture.h"
#include <vector>
#include "Enemy.h" // umieszczanie wrogów
#include "Block.h"
#include "Enemies_placer.h"
#include "BlockPlacer_module.h"

class Map
{
public:
	Map(const SDL_Rect & pos);

	void save_Objects(const std::string & name); // zapisuje dane wszystkich obiektów do pliku
	void load_Objects(const std::string & name); // ³aduje dane obiektów z pliku

	void events();
	void events_indp();

	void reset();

	void render();

	bool is_mouseOver() const { return mouse_over; }

	void set_background(const std::string & bg);

	const SDL_Rect & get_position() const { return edit_area; }
	// zwróæ obszar czêœci textury renderowanej na ekranie
	const SDL_Rect & get_backgroundArea() const { return mapBG_area; }
private:
	void mouse_handler();

	void Init_objectsSize();

	void update_events();
	void update_ObjectsSize();

	void placing_objects_events();
	void multi_selectingObject_events();
	void multi_selectingObject_mouseEvents();
	void single_selectingObject_events();
	void deleting_objects_events();
	void movingObject_mouseL_event();

	void placing_mouseL_Events();
	void placing_mouseR_Events();

	void create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);
	void create_EnemyOBJ(const SDL_Rect & mapPOS, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);

	void create_Block();
	void load_block();

	void events_enemies();
	void events_delete_enemies();

	void render_map();
	void render_enemies();

	void move_map_Wheel();
	void move_map_Mouse();
private:
	struct Moving_events {

	};

	static const int MAP_MOVE_SIZE = 20; // iloœæ pixeli przesuniêcia mapy

	bool mouse_over{ false };

	std::vector<Enemy*> enemies;
	std::vector<Block*> blocks;

	Enemy * current_enemy;

	Enemies_placer enemy_placerModule;

	Map_module * current_module{ &enemy_placerModule };

	std::ofstream save;
	std::ifstream load;

	SDL_Rect edit_area;
	SDL_Rect mapBG_area;

	SDL_Rect multi_selecting_area{};

	Enemy_data enemy_data;

	Texture mapBG;
};