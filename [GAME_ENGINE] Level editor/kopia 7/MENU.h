#pragma once
#include "MENU_Object.h"
#include <SDL_video.h>
#include "APP_State.h"
#include "Menu_State.h"

class MENU // g³ówna klasa menu
{
public:
	MENU(APP_state & state) : MainAPP{ state }, menu_state{ MENU_STATE::START_MENU } {}
	~MENU();

	void setMenus(const SDL_DisplayMode * dsp);

	void run_LC(SDL_Renderer * rn);
	void run_MC(SDL_Renderer * rn);
	void run_Start(SDL_Renderer * rn);
	void run_Paused(SDL_Renderer * rn);

	const MENU_STATE & getMenuState() const { return menu_state; }
private:
	void mSet_Start(const SDL_DisplayMode * dsp);
	void mSet_MC(const SDL_DisplayMode * dsp);
	void mSet_LC(const SDL_DisplayMode * dsp);
	void mSet_Pause(const SDL_DisplayMode * dsp);

	void render(SDL_Renderer * rn);
private:
	APP_state & MainAPP;

	MENU_STATE menu_state;

	MENU_Object menu_start, menu_MC, menu_LC, menu_pause;
};

