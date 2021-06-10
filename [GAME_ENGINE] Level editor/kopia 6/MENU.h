#pragma once
#include "MENU_Object.h"
#include <SDL_video.h>
#include "APP_State.h"
#include "Menu_State.h"

class MENU // g��wna klasa menu
{
public:
	MENU();
	~MENU();

	void setMenus(const SDL_DisplayMode * dsp);

	void run_LC(APP_state & app_state, SDL_Renderer * rn);
	void run_MC(APP_state & app_state, SDL_Renderer * rn);
	void run_Start(APP_state & app_state, SDL_Renderer * rn);
	void run_Paused(APP_state & app_state, SDL_Renderer * rn);

	const MENU_STATE & getMenuState() const { return menu_state; }
private:
	void mSet_Start(const SDL_DisplayMode * dsp);
	void mSet_MC(const SDL_DisplayMode * dsp);
	void mSet_LC(const SDL_DisplayMode * dsp);
	void mSet_Pause(const SDL_DisplayMode * dsp);

	void render(SDL_Renderer * rn);
private:
	MENU_STATE menu_state;
	MENU_Object menu_start, menu_MC, menu_LC, menu_pause;
};
