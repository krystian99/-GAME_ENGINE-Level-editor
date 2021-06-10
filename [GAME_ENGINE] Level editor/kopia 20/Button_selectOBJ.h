#pragma once
#include "Button_TEXT.h"
#include "EDIT_AREA_LC_state.h"

class Button_selectOBJ : public Button
{
public:
	Button_selectOBJ(EditArea_LC_state & st, EditArea_LC_state chng) :
		state{ st },
		to_chng{chng}
	{}

	void events();
	void render(SDL_Renderer * rn);

	~Button_selectOBJ() {}
private:
	void onMouseOver() {}
	void onClick();
private:
	EditArea_LC_state & state;
	EditArea_LC_state to_chng;
};

