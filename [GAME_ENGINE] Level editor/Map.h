#pragma once
#include "Rect.h"
#include <fstream>
#include "Texture.h"
#include <vector>
#include "Enemy.h" // umieszczanie wrogów
#include "Block.h"
#include "Enemies_placer.h"
#include "BlockPlacer_module.h"
#include <memory>

class singleOBJmove_structure : public Rect
{
public:
	void set(Enemy* enemy);

	void reset()
	{
		current_enemy = nullptr;
	}

	void events(bool mouse_over, SDL_Rect edit_area);

	Enemy* current_enemy;

	int px_left;
	int px_up;
};

class multiOBJ_select_structure : public Rect // struktura potrzebna zeby nie pomieszac danych oraz by zwiekszyc wydajnosc
{
public:
	struct Move_OBJ
	{
		Enemy* enemy;
		int px_up, px_left;
	};

	/*void set(SDL_Rect a)
	{
		area = { a.x, a.y, 1, 1 };
	}*/
	void set_borderOBJ(const Rect& pos, Enemy* enemy); //ustaw graniczne obiekty i dodaj do kontenera obiektow przenoszonych

	void render(const SDL_Rect& edit_area);
	void render();

	void events_moving(bool mouse_over, const SDL_Rect& edit_area);

	void reset(SDL_Rect a)
	{
		enemy_up = enemy_down = enemy_left = enemy_right = nullptr;
		moving_objects.clear();
		set(a.x, a.y, 1, 1);
	}

	void updateOBJs(SDL_Point clicked_point);

	//SDL_Rect area;

	int px_up, px_left;

	std::vector<Move_OBJ> moving_objects;

	Enemy* enemy_up{ nullptr }; // obiekt który jest najwyzej u góry
	Enemy* enemy_down{ nullptr };
	Enemy* enemy_left{ nullptr };
	Enemy* enemy_right{ nullptr };
};

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

	const SDL_Rect & get_position() const { return edit_area.get(); }
	// zwróæ obszar czêœci textury renderowanej na ekranie
	const SDL_Rect & get_backgroundArea() const { return mapBG_area.get(); }
private:
	void mouse_handler();

	void Init_objectsSize();

	void update_events();
	void update_ObjectsSize();

	void multi_selectingObject_events();
	void multi_selectingObject_mouseEvents();
	void multi_selecingOBJ_mouseR();
	void single_selectingObject_events();
	void deleting_objects_events();
	void movingObject_mouseL_event();
	void multi_movingObject_mouseR_event();
	void multiMoving_objects_events();

	void multiSelect_OBJs_set();

	void placing_mouseL_Events();
	void placing_mouseR_Events();

	void create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);
	void create_EnemyOBJ(const SDL_Rect & mapPOS, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);

	void events_enemies();
	void events_delete_enemies();

	void render_map();
	void render_enemies();

	void move_map_Wheel();
	void update_OBJs_renderPOS();
	void move_map_Mouse();
private:
	int MAP_MOVE_SIZE = 20; // iloœæ pixeli przesuniêcia mapy

	bool mouse_over{ false };

	std::vector<Enemy_ptr> enemies;

	bool pressing_mouseL_multiOBJ_select{ false };

	multiOBJ_select_structure multiOBJ_s; // struktura
	singleOBJmove_structure singleOBJmove_s;

	Enemy * current_enemy;

	Enemies_placer enemy_placerModule;

	Map_module * current_module{ &enemy_placerModule };

	Rect edit_area;
	Rect mapBG_area;

	Enemy_data enemy_data;

	Texture mapBG;
};