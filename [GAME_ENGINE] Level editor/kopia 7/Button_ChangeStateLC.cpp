#include "Button_ChangeStateLC.h"

Button_ChangeStateLC::Button_ChangeStateLC(LevelCreator_state & main_state, LevelCreator_state state_to_change) :
	EditorState{ main_state },
	switch_state{ state_to_change }
{
}

Button_ChangeStateLC::~Button_ChangeStateLC()
{
}

void Button_ChangeStateLC::onClick()
{

}
