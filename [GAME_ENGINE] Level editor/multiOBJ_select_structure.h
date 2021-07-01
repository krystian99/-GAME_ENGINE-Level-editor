#pragma once
#include "Rect.h"
#include "Module_base.h"
#include <vector>
#include "Map_mouseHandler.h"
#include "Enemy.h"

class multiOBJ_select_structure : public Rect, public Module_base // struktura potrzebna zeby nie pomieszac danych oraz by zwiekszyc wydajnosc
{
private:
	using Enemies = std::vector<Enemy_ptr>;
public:
	multiOBJ_select_structure(Enemies& en, const Map_mouseHandler& map_mouse, const Rect* edit_a, const Rect* mapBG_a);

	void render();

	bool isMoving() const { return is_movingOBJs; }
	// uruchamiane gdy zostanie zaznacozny obszar z obiektami do przeniesienia
	void OBJs_set(Enemies& enemy, const Rect& edit_area);

	void events();

	// wciœniêty lewy przycisk myszy
	void mouse_events();
	// zakoñczone przenoszenie i ustawienie obiektow na mapie
	void moveEvent_mouseR();

	void events_moving(bool mouse_over, const SDL_Rect& edit_area);
	void moveMap_Event();

	void update_renderPOS(int x, int y);

	//void update_mapX(int moveS);
	//void update_mapY(int moveS);

	int get_mapX() const { return mapPos.left(); }
	int get_mapY() const { return mapPos.up(); }

	void set_mapPOS(int x, int y);
	void set_mapPos(int x, int y, int w, int h);
	void set_mapPos(Rect&& area);

	void setX_map();
	void setY_map();
	void setW_map();
	void setH_map();

	void reset(SDL_Rect a);

	void updateOBJs(SDL_Point clicked_point);
private:
	void setState_movingOBJs(bool);
	void set_borderOBJ(const Rect& pos, Enemy* enemy); //ustaw graniczne obiekty i dodaj do kontenera obiektow przenoszonych

	//bool isMoving() const { return is_movingOBJs; }
private:
	struct Move_OBJ
	{
		Enemy* enemy;
		int px_up, px_left;
	};

	Rect mapPos;

	bool is_movingOBJs{ false };

	int px_up, px_left;

	std::vector<Move_OBJ> moving_objects;

	Enemy* enemy_up{ nullptr }; // obiekt który jest najwyzej u góry
	Enemy* enemy_down{ nullptr };
	Enemy* enemy_left{ nullptr };
	Enemy* enemy_right{ nullptr };

	Enemies& enemies;

	const Map_mouseHandler& map_mouseHandler;

	const Rect* edit_area;
	const Rect* mapBG_area;
};
