#pragma once
#include <SDL_render.h>
#include "ScrollBar.h"
#include "EDIT_AREA_LC.h"
#include "LevelCreator_state.h"
#include "Button_State_EA.h"
#include "CurrentScrollBar_state.h"
#include "Button_Change_SB.h"
#include "Button_DeleteOBJ.h"

#include "Button_TEST.h" // Testowy przycisk do analizy dzia�ania dodawania obiektu na obszar edycji
#include "Button_CNCLChoice.h" // Button_CancelChoise

#include "Button_load.h"
#include "Button_save.h"

#include "Button_Input.h"
// Na samym pocz�tku trzeba zrobi� wszystko, aby dzia�a�o. Dopiero potem mo�na bra� si� za wygl�d i optymalizacj�

class LevelCreator // odpowiada za sterowanie ca�ym LevelCreatorem, jest inicjatorem wszystkiego i g��wnym obiektem stan�w. Zezwala na sterowanie innymi obiektami, przydziela zadania.
{
public:
	LevelCreator();

	void Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH); // ustala pozycje wszystkich przycisk�w, scrollbarow itp. Inicjacja pocz�tkowa

	void events(SDL_Renderer * rn);
	void renderAll(SDL_Renderer * rn);
private:
	void Init_ScrollBars();
	void Init_ButtonsChangeSB(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_buttonTEST(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_EditArea(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_buttonDeleteOBJ(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_LoadSaveButtons(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_InputButton(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void events_ScrollBar(SDL_Renderer * rn);
	void events_ButtonsChangeSB(SDL_Renderer * rn);
private:
	EDIT_AREA_LC edition_area;

	Button_State_EA button_movingMAP, button_selectingOBJ; // zmieniaj� stan obszaru edycji obiektu Edition_area na odpowiednio "MOVING MAP" lub "SELECTING OBJ"
	Button_Change_SB DynamicCHNG, StaticCHNG, KeyCHNG, TEST_CHNG; // skr�t CHNG = CHANGE
	Button_CNCLChoice bt_CNCL; // anuluje wyb�r
	Button_DeleteOBJ bt_deleteOBJ;

	ScrollBar sbDynamic, sbKey, sbStatic;// , TEST;

	CurrentScrollBar cur_ScrollBar;

	Button_TEST testing;

	Button_load load_test;
	Button_save save_test;


	Button_Input input_test;
};

