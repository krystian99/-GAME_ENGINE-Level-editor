#pragma once
#include <SDL_render.h>
#include "EDIT_AREA_LC_state.h"
#include "EditArea_mainStates.h"
#include "Button_State_EA.h"
#include <vector>

//class LevelCreator;

/// ==============================
//  Skrót EA - Edition Area
/// ==============================

// v1 - testowanie i dodawanie odpowiednich dla obiektu danych
class EDIT_AREA_LC // musi byæ ten obiekt, poniewa¿ reprezentuje dane typowe dla obszaru edycji
{
	//friend class LevelCreator; // zaprzyjaŸniona klasa
	struct OBJ_TEST {
		Texture TX;
		int x, y;
	};
public:
	EDIT_AREA_LC() :
		button_movingMAP{ edit_state, EditArea_LC_state::MOVING_MAP },
		button_selectingOBJ{ edit_state, EditArea_LC_state::SELECTING_OBJECT },
		state_main{ EditArea_mainStates::NONE }
	{}
	~EDIT_AREA_LC() {}

	void Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void clearALL(); // czyœci dane wszystkich obiektów, które s¹ do³¹czone do obszaru edycji

	void events(SDL_Renderer * rn);

	EditArea_LC_state & getState() { return edit_state; }
private:
	void mouse_handler();

	void setPOS(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void render_ALL(SDL_Renderer * rn);
private:
	Button_State_EA button_movingMAP, button_selectingOBJ; // zmieniaj¹ stan obszaru edycji obiektu Edition_area na odpowiednio "MOVING MAP" lub "SELECTING OBJ"

	std::vector<OBJ_TEST> objects_test;

	SDL_Rect position;
	EditArea_LC_state edit_state;
	EditArea_mainStates state_main;
};

