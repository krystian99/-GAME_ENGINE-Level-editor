#pragma once
#include "Button_TEXT.h"
#include "Font.h"
#include "CurrentScrollBar_state.h"

class Button_Change_SB : public Button_TEXT
{
public:
	Button_Change_SB(CurrentScrollBar & state, CurrentScrollBar nextState) :
		current{ state }, next{ nextState }
	{}
	void render(SDL_Renderer * rn);

	void events();

	~Button_Change_SB() {}
private:
	virtual void onClick();
	virtual void onMouseOver();
private:
	CurrentScrollBar & current;
	CurrentScrollBar next;
};