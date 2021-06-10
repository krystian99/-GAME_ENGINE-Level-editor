#pragma once
//#include "Button.h"
#include "Button_TEXT.h"
#include "APP_State.h"
#include "Menu_State.h"
#include <string>
#include "Font.h"

class Button_Menu : public Button_TEXT
{
public:
	Button_Menu(APP_state & aMain, const APP_state & st2, MENU_STATE & mMain, const MENU_STATE & st1) :
		mainState_menu{ mMain }, nextMenu_state{ st1 },
		main_state{ aMain }, nextState{ st2 }
	{}

	void events(SDL_Renderer * rn);

	//void setRenderTEXT(std::string ttf_path, std::string renderedText, int height, SDL_Color color);

	~Button_Menu() {}
private:
	void render_all(SDL_Renderer * rn);
	
	void moveText(const int & size);

	virtual void onClick();
	virtual void onMouseOver();

	void set_nextState_APP();

	void TEXT_render(SDL_Renderer * rn);

	//void setPOS_TEXT(const SDL_Rect * rt);
private:
	static const int FRAME_SIZE = 10;
	static const int MoveSize = 4;

	APP_state & main_state;
	APP_state nextState;

	//SDL_Rect textPOS;

	//Font text;

	MENU_STATE & mainState_menu;
	MENU_STATE nextMenu_state;
};

