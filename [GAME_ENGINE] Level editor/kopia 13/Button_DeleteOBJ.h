#pragma once
#include "Button.h"
#include "EDIT_AREA_LC_state.h"

class Button_DeleteOBJ : public Button
{
public:
	Button_DeleteOBJ(EditArea_LC_state & state1) :
		edit_State{ state1 }
	{}
	~Button_DeleteOBJ() {}

	void events(SDL_Renderer * rn);
private:
	void onClick();
	void onMouseOver();
private:
	EditArea_LC_state & edit_State;
};