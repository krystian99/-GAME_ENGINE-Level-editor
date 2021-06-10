#pragma once
#include <SDL_render.h>
#include "EDIT_AREA_LC_state.h"
#include "EditArea_mainStates.h"
#include "Button_State_EA.h"
#include <vector>
#include "Texture.h"
#include <fstream>

//class LevelCreator;

/// ==============================
//  Skr�t EA - Edition Area
/// ==============================

// v1 - testowanie i dodawanie odpowiednich dla obiektu danych
// v2(02.04.2016) - dzia�a dodawanie testowych obiekt�w na map�
// v3(03.04.2016) - edycja obiektu, kt�ry jest ju� na�o�ony na map�(usuwanie, przemieszczanie, zmiana orientacji: przerzut poziomy textury)
// v4(04.04.2016) - zapisywanie levela testowego oraz jego wczytywanie z pliku
// v5 - zapisywanie oraz wczytywanie levela odbywa si� teraz inaczej. Na pocz�tku wczytywana jest nazwa levela z klawiatury.

struct Data {
	int x, y;
};

class OBJ_TEST {
public:
	OBJ_TEST(const int & x1, const int & y1);

	static const int w = 30;
	static const int h = 50;

	void setPOS(const SDL_Rect & rt);
	void set_mapPOS(const int & X, const int & Y);
	void setRenderPos(const int & render_X, const int & render_Y);

	const bool & is_clicked() const { return clicked; }

	void events();
	void render();

	const int & getX() const { return x; }
	const int & getY() const { return y; }

	const Data & getData() const { return data; }

	static void setTexture(const std::string & bg);
private:
	void mouse_handler();
private:
	SDL_Rect render_position;

	bool clicked;

	Data data;

	static Texture TX;
	int x, y; // pozycja wzgl�dem textury
};

class EDIT_AREA_LC;

class Map_area {
	friend class EDIT_AREA_LC;
public:
	Map_area(const Texture * tx) : TX{ tx } {}
	~Map_area() {}

	void Init(const SDL_Rect & rt);

	void setScale(const double & Scale);

	const SDL_Rect & getPOS() const { return area; }
private:
	bool canMove_r();
	bool canMove_l();
	bool canMove_u();
	bool canMove_d();
private:
	double scale;

	SDL_Rect area;
	const Texture * TX;
};

class EDIT_AREA_LC // musi by� ten obiekt, poniewa� reprezentuje dane typowe dla obszaru edycji
{
public:
	EDIT_AREA_LC() :
		state_main{ EditArea_mainStates::NONE },
		edit_state{ EditArea_LC_state::MOVING_MAP },
		current_enemy{ nullptr },
		map_renderArea{ &mapBG }
	{}
	~EDIT_AREA_LC() {}

	void Init();

	void load_MAP(const std::string & bg);

	void render();

	void saveLevel();

	bool loadLevel_test(const std::string & l_name);
	void createLevel_test(const std::string & l_name);

	void clearALL(); // czy�ci dane wszystkich obiekt�w, kt�re s� do��czone do obszaru edycji

	void events();

	EditArea_LC_state & get_editState() { return edit_state; }
	EditArea_mainStates & get_mainState() { return state_main; }
private:
	void mouse_handler();

	void render_eventsDependent();

	void setPOS();
	void setMap_renderArea();
	
	void setMap_view();

	void renderBackground();
	void renderEnemies();
	void renderBlocks();

	void events_enemies();

	void createOBJ(const int & X, const int & Y);

	void on_buttonL_MouseClick(const int & mX, const int & mY);
	void on_buttonL_MousePress(const int & mX, const int & mY);

	void placingObjects_events();
	void movingMap_events();
	void selecingObjects_events();
	void deletingObjects_events();
	void movingOBJ_events();
private:
	Texture test_objectTX;
	Texture mapBG; // t�o mapy, na kt�ry b�d� nak�adane obiekty

	std::vector<OBJ_TEST> objects_test;

	EditArea_LC_state next_event;

	SDL_Rect position;

	Map_area map_renderArea;

	EditArea_LC_state edit_state;
	EditArea_mainStates state_main;

	SDL_Rect mouse_updateDraw;

	bool lBT_clicked;

	OBJ_TEST * current_enemy;

	std::string level_name;

	std::ofstream save;
	std::ifstream load;

	Data data_object_test;

	bool moving_map;
};