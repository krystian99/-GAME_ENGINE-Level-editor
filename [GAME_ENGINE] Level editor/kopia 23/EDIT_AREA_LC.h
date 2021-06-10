#pragma once
#include <SDL_render.h>
#include "EDIT_AREA_LC_state.h"
#include "EditArea_mainStates.h"
#include "Button_State_EA.h"
#include <list>
#include "Texture.h"
#include <fstream>

//class LevelCreator;

/// ==============================
//  Skrót EA - Edition Area
/// ==============================

// v1 - testowanie i dodawanie odpowiednich dla obiektu danych
// v2(02.04.2016) - dzia³a dodawanie testowych obiektów na mapê
// v3(03.04.2016) - edycja obiektu, który jest ju¿ na³o¿ony na mapê(usuwanie, przemieszczanie, zmiana orientacji: przerzut poziomy textury)
// v4(04.04.2016) - zapisywanie levela testowego oraz jego wczytywanie z pliku
// v5 - zapisywanie oraz wczytywanie levela odbywa siê teraz inaczej. Na pocz¹tku wczytywana jest nazwa levela z klawiatury.

struct Data {
	int x, y;
	//double renderScaleX, renderScaleY;
};

class OBJ_TEST {
public:
	OBJ_TEST(const int & x1, const int & y1, const double & scaleW, const double & scaleH);

	static const int w = 30;
	static const int h = 50;

	void setID(std::list<OBJ_TEST>::iterator iterator);
	void setPOS(const SDL_Rect & rt);
	void setRenderPos(const int & render_X, const int & render_Y);

	void move_renderX(int sizeX);
	void move_renderY(int sizeY);

	const bool & is_clicked() const { return clicked; }

	void events();
	void render(SDL_Renderer * rn);// , const int & posX, const int & posY);

	const int & getX() const { return x; }
	const int & getY() const { return y; }

	const double & getScaleX() const { return ScaleX; }
	const double & getScaleY() const { return ScaleY; }

	const Data & getData() const { return data; }

	const std::list<OBJ_TEST>::iterator & getID() const { return ID; }

	static void setTexture(const std::string & bg);
private:
	void mouse_handler();
private:
	std::list<OBJ_TEST>::iterator ID;

	SDL_Rect position;
	SDL_Rect render_position;

	bool clicked;

	Data data;

	const double ScaleX, ScaleY;

	static Texture TX;
	int x, y; // pozycja wzglêdem textury
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

	/*void setView();
	void setView_v2();
	void setView(std::list<OBJ_TEST> & objects);*/
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

class EDIT_AREA_LC // musi byæ ten obiekt, poniewa¿ reprezentuje dane typowe dla obszaru edycji
{
public:
	EDIT_AREA_LC() :
		state_main{ EditArea_mainStates::NONE },
		//edit_state{ EditArea_LC_state::NONE },
		edit_state{ EditArea_LC_state::MOVING_MAP },
		current_enemy{ nullptr },
		map_renderArea{ &mapBG }
	{}
	~EDIT_AREA_LC() {}

	void Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void load_MAP(const std::string & bg);

	void render(SDL_Renderer * rn);

	void saveLevel();

	bool loadLevel_test(const std::string & l_name);
	void createLevel_test(const std::string & l_name);

	void clearALL(); // czyœci dane wszystkich obiektów, które s¹ do³¹czone do obszaru edycji

	void events(SDL_Renderer * rn);

	EditArea_LC_state & get_editState() { return edit_state; }
	EditArea_mainStates & get_mainState() { return state_main; }
private:
	void mouse_handler();

	void render_eventsDependent(SDL_Renderer * rn);

	void setPOS(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void setMap_renderArea();
	
	void setMap_view();

	void renderBackground(SDL_Renderer * rn);
	void renderEnemies(SDL_Renderer * rn);
	void renderBlocks(SDL_Renderer * rn);

	void events_enemies();

	void createOBJ(const int & X, const int & Y);// , const double & scaleX, const double & scaleY);

	void on_buttonL_MouseClick(const int & mX, const int & mY);
	void on_buttonL_MousePress(const int & mX, const int & mY);

	void placingObjects_events(SDL_Renderer * rn);
	void movingMap_events();
	void selecingObjects_events();
	void deletingObjects_events();
	void movingOBJ_events(SDL_Renderer * rn);
private:
	Texture test_objectTX;
	Texture mapBG; // t³o mapy, na który bêd¹ nak³adane obiekty

	std::list<OBJ_TEST> objects_test;

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

	double scaleScreenW, scaleScreenH;

	bool moving_map;
};