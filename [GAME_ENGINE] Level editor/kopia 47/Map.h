#pragma once
#include <SDL_rect.h>
#include <fstream>
#include "Texture.h"
#include "Enemy.h"
#include <vector>

class Map
{
public:
	Map(const SDL_Rect & pos);

	void save_Objects(const std::string & name); // zapisuje dane wszystkich obiekt�w do pliku
	void load_Objects(const std::string & name); // �aduje dane obiekt�w z pliku

	void events();
	void events_indp();

	void reset();

	void render();

	const bool & is_mouseOver() const { return mouse_over; }

	void set_background(const std::string & bg);

	const SDL_Rect & get_position() const { return edit_area; }
	// zwr�� obszar cz�ci textury renderowanej na ekranie
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

	void placing_mouseL_Events();
	void placing_mouseR_Events();

	void create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);
	void create_EnemyOBJ(const SDL_Rect & mapPOS, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);

	void events_enemies();
	void events_delete_enemies();

	void render_map();
	void render_enemies();

	void move_map_Wheel();
	void move_map_Mouse();
private:
	static const int MAP_MOVE_SIZE = 20; // ilo�� pixeli przesuni�cia mapy

	bool mouse_over{ false };

	std::vector<Enemy*> enemies;

	Enemy * current_enemy;

	std::ofstream save;
	std::ifstream load;

	SDL_Rect edit_area;
	SDL_Rect mapBG_area;

	SDL_Rect multi_selecting_area{};

	Enemy_data enemy_data;

	Texture mapBG;
};