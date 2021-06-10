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

//#include "Button_load.h"
#include "Button_save.h"

#include "Button_Input.h"
#include "Button_selectOBJ.h"
// Na samym pocz�tku trzeba zrobi� wszystko, aby dzia�a�o. Dopiero potem mo�na bra� si� za wygl�d i optymalizacj�

class LevelCreator // odpowiada za sterowanie ca�ym LevelCreatorem, jest inicjatorem wszystkiego i g��wnym obiektem stan�w. Zezwala na sterowanie innymi obiektami, przydziela zadania.
{
public:
	LevelCreator();

	void Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH); // ustala pozycje wszystkich przycisk�w, scrollbarow itp. Inicjacja pocz�tkowa

	bool loadLevel(const std::string & level_name);
	void newLevel(const std::string & level_name);

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

	Button_State_EA button_movingMAP, button_selectingOBJ; // zmieniaj� stan obszaru edycji obiektu Edition_area na odpowiednio "MOVING MAP" lub "SELECTING OBJ"
	Button_Change_SB DynamicCHNG, StaticCHNG, KeyCHNG, TEST_CHNG; // skr�t CHNG = CHANGE
	Button_DeleteOBJ bt_deleteOBJ;

	ScrollBar sbDynamic, sbKey, sbStatic;

	CurrentScrollBar cur_ScrollBar;

	Button_TEST testing;

	Button_save save_test;

	EditArea_LC_state editArea_state;

	Button_Input input_test;
	Button_selectOBJ bt_select;

	LevelCreator_state mainState;
};

