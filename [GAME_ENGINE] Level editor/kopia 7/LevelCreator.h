#pragma once
#include <SDL_render.h>
#include "ScrollBar.h"
#include "EDIT_AREA_LC.h"
#include "LevelCreator_state.h"
#include "Button_State_EA.h"

// v1 - dodano klasê

class LevelCreator // odpowiada za generowanie w³aœciwego kodu Ÿród³owego, za umieszczanie obiektów na okreœlonych pozycjach
{
public:
	LevelCreator();

	void Init(const SDL_DisplayMode * dm, const int & scaleW, const int & scaleH); // ustala pozycje wszystkich przycisków, scrollbarow itp. Inicjacja pocz¹tkowa

	void events(SDL_Renderer * rn);
private:
	void Init_ScrollBars();
	void Init_IndependentButtons();

	void switch_events();
	void events_ScrollBars(SDL_Renderer * rn);
	void events_EditArea(SDL_Renderer * rn);
private:
	EDIT_AREA_LC edition_area;

	Button_State_EA button_movingMAP, button_selectingOBJ; // zmieniaj¹ stan obszaru edycji obiektu Edition_area na odpowiednio "MOVING MAP" lub "SELECTING OBJ"

	ScrollBar sbDynamic, sbKey, sbStatic;

	CurrentScrollBar cur_ScrollBar;

	//Edit_area edition_area;
	LevelCreator_state stateLC;
};

