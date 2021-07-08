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
	multiOBJ_select_structure(Enemies& en, const Map_mouseHandler& map_mouse, const Rect* edit_a, const Rect* mapBG_a);

	void render();

	bool isMoving() const { return is_movingOBJs; }

	void reset();

	void events();

	void events_indp();

private:
	// uruchamiane gdy zostanie zaznacozny obszar z obiektami do przeniesienia
	void OBJs_set();

	// przenoszenie obiektów
	void events_moving();

	// zakoñczone przenoszenie i ustawienie obiektow na mapie
	void movingFinsh_event();

	void moveMap_Event();

	void updateOBJs(SDL_Point clicked_point);

	void setState(States st) { state = st; }

	void setState_movingOBJs(bool);
	void set_borderOBJ(const Rect& pos, Enemy* enemy); //ustaw graniczne obiekty i dodaj do kontenera obiektow przenoszonych

	void selectingOBJs();

	void on_mouseL1hit() override;
	void on_mouseR1hit() override;
	//void on_mouseW1hit() {}

	void on_mouseOver() override; // gdy myszka na pozycji obiektu
	void on_mouseOut() override; // gdy myszka nie jest ju¿ na pozycji przycisku

	// gdy trzymany przez jakiœ czas przycisk myszy
	void on_mouseL_press() override;
	void on_mouseR_press() override;
	//virtual void on_mouseW_press() {}

	void on_mouseL_pressUP() override;

	void on_keyboardKey_DELETE_1hit() override;

	//bool isMoving() const { return is_movingOBJs; }
private:
	struct Move_OBJ
	{
		Enemy* enemy;
		int px_up, px_left;
	};

	struct SelectedArea_data
	{
		int renderX, renderY, renderW, renderH;
		int mapX, mapY, mapW, mapH;
	};

	SelectedArea_data sa_data;

	Point clicked_point;

	Rect mapPos;

	bool is_movingOBJs{ false };

	int px_up, px_left;

	std::vector<Move_OBJ> moving_objects;

	Enemy* enemy_up{ nullptr }; // obiekt który jest najwyzej u góry
	Enemy* enemy_down{ nullptr };
	Enemy* enemy_left{ nullptr };
	Enemy* enemy_right{ nullptr };

	Enemies& enemies;

	MapOBJ selected_area;

	States state{ States::SELECTING_OBJs };

	const Map_mouseHandler& map_mouseHandler;

	const Rect* edit_area;
	const Rect* mapBG_area;
};
