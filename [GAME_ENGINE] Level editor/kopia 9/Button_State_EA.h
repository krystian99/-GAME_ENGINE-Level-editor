#pragma once
#include "Button.h"
#include "EDIT_AREA_LC_state.h"

class Button_State_EA : public Button // zmienia stan obszaru edycji na przesuwanie mapy lub przemieszczanie obiektów
{
public:
	Button_State_EA(EditArea_LC_state & st, EditArea_LC_state to_change);

	~Button_State_EA() {}
private:
	virtual void onClick();
	virtual void onMouseOver();
private:
	EditArea_LC_state & state;
	EditArea_LC_state state_to_change;
};

