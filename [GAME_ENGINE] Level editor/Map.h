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
#include "CoordinateBar_mouse.h"
#include "Map_mouseHandler.h"

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
private:
	using Enemies = std::vector<Enemy_ptr>;
public:
	multiOBJ_select_structure(){}
	multiOBJ_select_structure(const Rect* edit_a, const Rect* mapBG_a);

	void set_borderOBJ(const Rect& pos, Enemy* enemy); //ustaw graniczne obiekty i dodaj do kontenera obiektow przenoszonych

	void render(const SDL_Rect& edit_area);
	void render();

	void OBJs_set(Enemies& enemy, const Rect & edit_area);

	void events(const Rect& edit_area, Enemies & enemies);
	void mouse_events(bool, const Map_mouseHandler &);
	void moveEvent_mouseR(Enemies&, const Rect&, const Rect&);

	void events_moving(bool mouse_over, const SDL_Rect& edit_area);
	void mouseWheel_events(int moveS);

	void update_renderPOS(int x, int y);

	void update_mapX(int moveS);
	void update_mapY(int moveS);

	int get_mapX() const { return mapPos.left(); }
	int get_mapY() const { return mapPos.up(); }

	void set_mapPos(Rect && area);
	void set_mapPos(int x, int y, int w, int h);
	void setX_map();
	void setY_map();
	void setW_map();
	void setH_map();

	void reset(SDL_Rect a)
	{
		enemy_up = enemy_down = enemy_left = enemy_right = nullptr;
		moving_objects.clear();
		set(a.x, a.y, 1, 1);
	}

	void updateOBJs(SDL_Point clicked_point);
private:
	struct Move_OBJ
	{
		Enemy* enemy;
		int px_up, px_left;
	};

	Rect mapPos;

	int px_up, px_left;

	std::vector<Move_OBJ> moving_objects;

	Enemy* enemy_up{ nullptr }; // obiekt który jest najwyzej u góry
	Enemy* enemy_down{ nullptr };
	Enemy* enemy_left{ nullptr };
	Enemy* enemy_right{ nullptr };

	const Rect* edit_area;
	const Rect* mapBG_area;
};

class Map
{
public:
	Map(const SDL_Rect & pos);

	void save_Objects(const std::string & name); // zapisuje dane wszystkich obiektów do pliku
	void load_Objects(const std::string & name); // ³aduje dane obiektów z pliku

	void events();
	void events_indp();

	void set_cord(const CoordinateBar_mouse* mouse_cord);

	void reset();

	void render();

	const bool & is_mouseOver() const { return mouse_over; }

	void set_background(const std::string & bg);

	const SDL_Rect & get_position() const { return edit_area.get(); }
	// zwróæ obszar czêœci textury renderowanej na ekranie
	const SDL_Rect & get_backgroundArea() const { return mapBG_area.get(); }
private:
	void set_ScaledSize();

	void mouseR_events();
	void mouseWheel_events();

	void mouse_handler();

	void Init_objectsSize();

	void update_events();
	void update_ObjectsSize();

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
	Map_mouseHandler map_mouseHandler;

	const CoordinateBar_mouse* mouse_cord;
	int scaleMapX;
	int scaleMapY;

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