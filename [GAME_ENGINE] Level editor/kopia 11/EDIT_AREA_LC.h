#pragma once
#include <SDL_render.h>
#include "EDIT_AREA_LC_state.h"
#include "EditArea_mainStates.h"
#include "Button_State_EA.h"
#include "OBJ_id.h"
#include <vector>
#include "Texture.h"

//class LevelCreator;

/// ==============================
//  Skrót EA - Edition Area
/// ==============================

// v1 - testowanie i dodawanie odpowiednich dla obiektu danych
// v2(02.04.2016) - dzia³a dodawanie testowych obiektów na mapê
// v3 - edycja obiektu, który jest ju¿ na³o¿ony na mapê(usuwanie, przemieszczanie, zmiana orientacji: przerzut poziomy textury)

class EDIT_AREA_LC // musi byæ ten obiekt, poniewa¿ reprezentuje dane typowe dla obszaru edycji
{
	//friend class LevelCreator; // zaprzyjaŸniona klasa
	Texture test_objectTX;

	class OBJ_TEST {
	public:
		OBJ_TEST(int x1, int y1, int index1);

		static const int w = 30;
		static const int h = 50;

		const int & getID() const { return index; }

		bool is_clicked() { return clicked; }

		void events(SDL_Renderer * rn);

		void setID(int id);

		static void setTexture(std::string bg);
		void render(SDL_Renderer * rn);
	private:
		void mouse_handler();

		//void render(SDL_Renderer * rn);
	private:
		int index;

		SDL_Rect position;

		bool clicked;

		static Texture TX;
		int x, y;
	};
public:
	EDIT_AREA_LC() :
		/*button_movingMAP{ edit_state, EditArea_LC_state::MOVING_MAP },
		button_selectingOBJ{ edit_state, EditArea_LC_state::SELECTING_OBJECT },*/
		state_main{ EditArea_mainStates::NONE },
		edit_state{ EditArea_LC_state::NONE }
	{}
	~EDIT_AREA_LC() {}

	void Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void load_MAP(const std::string & bg);

	void clearALL(); // czyœci dane wszystkich obiektów, które s¹ do³¹czone do obszaru edycji

	void events(SDL_Renderer * rn);

	EditArea_LC_state & get_editState() { return edit_state; }
	EditArea_mainStates & get_mainState() { return state_main; }
private:
	void mouse_handler(SDL_Renderer * rn);

	void setPOS(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void renderBackground(SDL_Renderer * rn);

	void render_ALL(SDL_Renderer * rn);
	void renderEnemies(SDL_Renderer * rn);
	void renderBlocks(SDL_Renderer * rn);

	void events_enemies(SDL_Renderer * rn);

	void placingObjects_events(SDL_Renderer * rn);
	void movingMap_events(SDL_Renderer * rn);
	void selecingObjects_events(SDL_Renderer * rn);
	void deletingObjects_events(SDL_Renderer * rn);

private:
	//Button_State_EA button_movingMAP, button_selectingOBJ; // zmieniaj¹ stan obszaru edycji obiektu Edition_area na odpowiednio "MOVING MAP" lub "SELECTING OBJ"
	Texture mapBG; // t³o mapy, na który bêd¹ nak³adane obiekty

	std::vector<OBJ_TEST> objects_test;

	struct Creating_OBJ {
		OBJ_id type;
	};

	SDL_Rect position;

	EditArea_LC_state edit_state;
	EditArea_mainStates state_main;

	SDL_Rect mouse_updateDraw;

	bool lBT_clicked;

	int currentOBJ_ID;
};