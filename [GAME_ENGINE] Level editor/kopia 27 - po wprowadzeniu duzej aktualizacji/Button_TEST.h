#pragma once
#include "EditArea_mainStates.h"
#include "EDIT_AREA_LC_state.h"
#include "Button_TEXT.h"

class Button_TEST : public Button_TEXT
{
public:
	Button_TEST(EditArea_LC_state & state1, EditArea_mainStates & state2) :
		edit_State{ state1 },
		edit_mainState{ state2 }
	{}
	~Button_TEST() {}

	void render();

	void events();
private:
	void onClick();
	void onMouseOver();

	void TEXT_render();
private:
	EditArea_LC_state & edit_State;
	EditArea_mainStates & edit_mainState;
};

