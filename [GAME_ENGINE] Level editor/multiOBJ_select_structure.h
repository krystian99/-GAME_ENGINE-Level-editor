#pragma once
#include "Rect.h"
#include "Module_base.h"
#include <vector>
#include "Map_mouseHandler.h"
#include "Enemy.h"
#include "MapOBJ.h"

class multiOBJ_select_structure final : public Object, public Module_base // struktura potrzebna zeby nie pomieszac danych oraz by zwiekszyc wydajnosc
{
	enum class States { 
		NONE,
		SELECTING_OBJs,
		MOVING_OBJs,
		SET_OBJs
	};
	using Enemies = std::vector<Enemy_ptr>;
public:
	multiOBJ_select_structure(Enemies& en, const Rect* edit_a, const Rect* mapBG_a);

	void render();

	void reset();

	void events() override;
private:
	// uruchamiane gdy zostanie zaznacozny obszar z obiektami do przeniesienia
	void OBJs_set();

	// przenoszenie obiektów
	void events_moving();

	// zakoñczone przenoszenie i ustawienie obiektow na mapie
	void movingFinsh_event();

	void moveMap_Event();

	void updateOBJs();

	void setState(States st) { state = st; }

	void set_borderOBJ(const Rect& pos, Enemy* enemy); //ustaw graniczne obiekty i dodaj do kontenera obiektow przenoszonych

	void selectingOBJs();

	void on_mouseL1hit() override;
	void on_mouseR1hit() override;

	void on_mouseL_press() override;
	void on_mouseL_pressUP() override;

	void on_mouseWheel_up_1hit() override;
	void on_mouseWheel_down_1hit() override;

	void on_keyboardKey_DELETE_1hit() override;
private:
	struct Move_OBJ
	{
		void updatePOS(int upd_renderX, int upd_renderY, int upd_mapX, int upd_mapY);
		void setPOS(int renderX, int renderY, int mapX, int mapY);

		Enemy* enemy;
		int px_up, px_left;
		int map_pxUP, map_pxLEFT;
	};

	Point clicked_point, clicked_pointMap;

	Rect mapPos;

	int px_up, px_left;

	std::vector<Move_OBJ> moving_objects;

	// obiekt który jest najwyzej u góry
	Enemy* enemy_up{ nullptr };
	Enemy* enemy_down{ nullptr };
	Enemy* enemy_left{ nullptr };
	Enemy* enemy_right{ nullptr };

	Enemies& enemies;

	MapOBJ selected_area;

	States state{ States::SELECTING_OBJs };

	const Rect* edit_area;
	const Rect* mapBG_area;
};
