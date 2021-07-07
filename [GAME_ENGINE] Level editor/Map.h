#pragma once
#include "Rect.h"
#include <fstream>
#include "Texture.h"
#include <vector>
#include "Enemy.h"
#include "Block.h"
#include "BlockPlacer_module.h"
#include <memory>
#include "CoordinateBar_mouse.h"
#include "Map_mouseHandler.h"
#include "Map_events.h"

#include "Module_base.h"

#include "Enemies_placer.h"
#include "multiOBJ_select_structure.h"
#include "DeleteOBJ_structure.h"
#include "singleOBJmove_structure.h"
#include "Map_moveMouse_module.h"

// klasa steruj¹ca wszystkimi zdarzeniami na mapie
class Map
{
	friend void Map_events::render_enemies(Map* map);
	friend void Map_events::render_map(Map* map);

	friend void Map_events::events_enemies(Map* map);
public:
	Map(int x, int y, int w, int h);

	bool isUpdated() const { return updated; }

	void save_Objects(const std::string & name); // zapisuje dane wszystkich obiektów do pliku
	void load_Objects(const std::string & name); // ³aduje dane obiektów z pliku

	void events();
	void events_indp();

	void set_cord(const CoordinateBar_mouse* mouse_cord);

	void reset();

	void render();

	const bool & is_mouseOver() const { return mouse_over; }

	void set_background(const std::string & bg);

	const SDL_Rect & get_position() const { return edit_area.get_position(); }
	// zwróæ obszar czêœci textury renderowanej na ekranie
	const SDL_Rect & get_backgroundArea() const { return mapBG_area.get_position(); }
private:
	void set_ScaledSize();

	void mouseR_events();
	void mouseWheel_events();

	void mouse_handler();

	void Init_objectsSize();

	void update_events();
	//void update_ObjectsSize();

	void multi_selectingObject_mouseEvents();
	void multi_selecingOBJ_mouseR();

	void deleting_objects_events();

	void multi_movingObject_mouseR_event();
	void multiMoving_objects_events();

	void multiSelect_OBJs_set();

	void placing_mouseL_Events();
	//void placing_mouseR_Events();

	void create_EnemyOBJ(const int & X, const int & Y, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);
	void create_EnemyOBJ(const SDL_Rect & mapPOS, const Enemy_ID & id, const SDL_RendererFlip & flip = SDL_FLIP_NONE);

	void events_enemies();
	void events_delete_enemies();

	void render_map();
	void render_enemies();

	void move_map_Wheel();

	void moveMap_eventWheelUP();
	void moveMap_eventWheelDOWN();

	void update_OBJs_renderPOS();
	void move_map_Mouse();
private:
	Map_mouseHandler map_mouseHandler;

	const CoordinateBar_mouse* mouse_cord;

	int scaleMapX;
	int scaleMapY;

	int MAP_MOVE_SIZE = 20; // iloœæ pixeli przesuniêcia mapy

	bool updated{ true };

	bool mouse_over{ false };

	std::vector<Enemy_ptr> enemies;

	bool pressing_mouseL_multiOBJ_select{ false };

	// modu³y mapy
	DeleteOBJ_structure deleteOBJ_s;
	Enemies_placer enemy_placerModule;
	multiOBJ_select_structure multiOBJ_s;
	singleOBJmove_structure singleOBJmove_s;
	Map_moveMouse_module map_MOVE_mouse_s;

	//Module_base* current{ &multiOBJ_s };

	Enemies_placer * current_module{ &enemy_placerModule };

	Enemy* current_enemy;

	Rect edit_area;
	Rect mapBG_area;

	Texture mapBG;
};
