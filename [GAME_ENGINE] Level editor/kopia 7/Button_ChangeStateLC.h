#pragma once
#include "Button.h"
#include "LevelCreator_state.h"

class Button_ChangeStateLC : Button
{
public:
	Button_ChangeStateLC(LevelCreator_state & main_state, LevelCreator_state state_to_change);
	~Button_ChangeStateLC();
private:
	virtual void onClick();
private:
	LevelCreator_state & EditorState;

	LevelCreator_state switch_state;
};

