#include "Button_State_EA.h"




Button_State_EA::Button_State_EA(EditArea_LC_state & st, EditArea_LC_state to_change) :
	state{ st },
	state_to_change{ to_change }
{}

void Button_State_EA::onClick()
{
	state = state_to_change;
}

void Button_State_EA::onMouseOver()
{

}
