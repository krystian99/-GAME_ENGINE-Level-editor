#pragma once
#include <SDL_render.h>
#include "EDIT_AREA_LC_state.h"
#include "EditArea_mainStates.h"
#include "Button_State_EA.h"
#include "OBJ_id.h"
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

class OBJ_TEST {
public:
	OBJ_TEST(int x1, int y1);

	static const int w = 30;
	static const int h = 50;

	void setID(std::list<OBJ_TEST>::iterator iterator);

	const bool & is_clicked() const { return clicked; }

	void events();
	void render(SDL_Renderer * rn);

	const int & getX() const { return x; }
	const int & getY() const { return y; }

	const std::list<OBJ_TEST>::iterator & getID() const { return ID; }

	static void setTexture(std::string bg);
private:
	void mouse_handler();
private:
	std::list<OBJ_TEST>::iterator ID;

	SDL_Rect position;

	bool clicked;

	static Texture TX;
	int x, y;
};

class EDIT_AREA_LC // musi byæ ten obiekt, poniewa¿ reprezentuje dane typowe dla obszaru edycji
{
	//friend class LevelCreator; // zaprzyjaŸniona klasa
	Texture test_objectTX;
public:
	EDIT_AREA_LC() :
		state_main{ EditArea_mainStates::NONE },
		edit_state{ EditArea_LC_state::NONE },
		current_enemy{ nullptr }
	{}
	~EDIT_AREA_LC() {}

	void Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void load_MAP(const std::string & bg);

	void render(SDL_Renderer * rn);

	void saveLevel();
	void loadLevel();

	void clearALL(); // czyœci dane wszystkich obiektów, które s¹ do³¹czone do obszaru edycji

	void events();

	EditArea_LC_state & get_editState() { return edit_state; }
	EditArea_mainStates & get_mainState() { return state_main; }
private:
	void mouse_handler();

	void setPOS(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void renderBackground(SDL_Renderer * rn);
	void renderEnemies(SDL_Renderer * rn);
	void renderBlocks(SDL_Renderer * rn);

	void events_enemies();

	void createOBJ(int mX, int mY);

	void placingObjects_events();
	void movingMap_events();
	void selecingObjects_events();
	void deletingObjects_events();

private:
	Texture mapBG; // t³o mapy, na który bêd¹ nak³adane obiekty

	std::list<OBJ_TEST> objects_test;

	SDL_Rect position;

	EditArea_LC_state edit_state;
	EditArea_mainStates state_main;

	SDL_Rect mouse_updateDraw;

	bool lBT_clicked;

	OBJ_TEST * current_enemy;

	std::string level_name;

	std::ofstream save;
	std::ifstream load;
};