#pragma once
#include <SDL_rect.h>
#include <fstream>
#include "Texture.h"
#include "Enemy.h"
#include <vector>

class Map_EditArea
{
public:
	Map_EditArea(const SDL_Rect & pos);

	void save_Objects(const std::string & name); // zapisuje dane wszystkich obiektów do pliku
	void load_Objects(const std::string & name); // ³aduje dane obiektów z pliku

	void events();
	void events_indp();

	void reset();

	void render();

	const bool & is_mouseOver() const { return mouse_over; }

	void set_background(const std::string & bg);

	const SDL_Rect & get_position() const { return edit_area; }
	// zwróæ obszar czêœci textury renderowanej na ekranie
	const SDL_Rect & get_backgroundArea() const { return mapBG_area; }

	~Map_EditArea() {}
private:
	void mouse_handler();

	void placing_objects_events();
	void multi_selecingObject_events();
	void multi_selecingObject_mouseEvents();
	void single_selecingObject_events();
	void deleting_objects_events();
	void moving_objects_events();

	void placing_mouseL_Events();
	void placing_mouseR_Events();

	void create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);

	void events_enemies();

	void render_map();
	void render_enemies();

	void move_map_Wheel();
	void move_map_Mouse();
private:
	static const int MAP_MOVE_SIZE = 20; // iloœæ pixeli przesuniêcia mapy

	bool mouse_over;

	std::vector<Enemy*> enemies;
	std::vector<Base_OBJ*> trash_objects;

	Enemy * current_enemy;

	std::ofstream save;
	std::ifstream load;

	SDL_Rect edit_area;
	SDL_Rect mapBG_area;

	SDL_Rect multi_selecting_area;

	Enemy_data enemy_data;

	Texture mapBG;
};