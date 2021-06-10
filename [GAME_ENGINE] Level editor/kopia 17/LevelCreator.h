#pragma once
#include <SDL_render.h>
#include "ScrollBar.h"
#include "EDIT_AREA_LC.h"
#include "LevelCreator_state.h"
#include "Button_State_EA.h"
#include "CurrentScrollBar_state.h"
#include "Button_Change_SB.h"
#include "Button_DeleteOBJ.h"

#include "Button_TEST.h" // Testowy przycisk do analizy dzia³ania dodawania obiektu na obszar edycji
#include "Button_CNCLChoice.h" // Button_CancelChoise

#include "Button_load.h"
#include "Button_save.h"

#include "Button_Input.h"
#include "Button_selectOBJ.h"
// Na samym pocz¹tku trzeba zrobiæ wszystko, aby dzia³a³o. Dopiero potem mo¿na braæ siê za wygl¹d i optymalizacjê

class LevelCreator // odpowiada za sterowanie ca³ym LevelCreatorem, jest inicjatorem wszystkiego i g³ównym obiektem stanów. Zezwala na sterowanie innymi obiektami, przydziela zadania.
{
public:
	LevelCreator();

	void Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH); // ustala pozycje wszystkich przycisków, scrollbarow itp. Inicjacja pocz¹tkowa

	void events(SDL_Renderer * rn);
	void render(SDL_Renderer * rn);
private:
	void Init_ScrollBars();
	void Init_ButtonsChangeSB(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_buttonTEST(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_EditArea(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_buttonDeleteOBJ(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_LoadSaveButtons(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);
	void Init_InputButton(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH);

	void events_ScrollBar();
	void events_ButtonsChangeSB();

	void render_ScrollBars(SDL_Renderer * rn);
	void render_ButtonsChangeSB(SDL_Renderer * rn);
private:
	EDIT_AREA_LC edition_area;

	Button_State_EA button_movingMAP, button_selectingOBJ; // zmieniaj¹ stan obszaru edycji obiektu Edition_area na odpowiednio "MOVING MAP" lub "SELECTING OBJ"
	Button_Change_SB DynamicCHNG, StaticCHNG, KeyCHNG, TEST_CHNG; // skrót CHNG = CHANGE
	Button_CNCLChoice bt_CNCL; // anuluje wybór
	Button_DeleteOBJ bt_deleteOBJ;

	ScrollBar sbDynamic, sbKey, sbStatic;

	CurrentScrollBar cur_ScrollBar;

	Button_TEST testing;

	Button_load load_test;
	Button_save save_test;

	EditArea_LC_state editArea_state;

	Button_Input input_test;
	Button_selectOBJ bt_select;
};

