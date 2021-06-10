#include "MENU.h"



MENU::MENU()
{
}


MENU::~MENU()
{
}

void MENU::setMenus(const SDL_DisplayMode * dsp)
{
	mSet_Start(dsp);
	mSet_LC(dsp);
	mSet_MC(dsp);
}

void MENU::run_LC(APP_state & app_state, SDL_Renderer * rn)
{

}

void MENU::run_MC(APP_state & app_state, SDL_Renderer * rn)
{
	menu_MC.events(app_state, menu_state);
}

void MENU::run_Start(APP_state & app_state, SDL_Renderer * rn)
{

}

void MENU::run_Paused(APP_state & app_state, SDL_Renderer * rn)
{

}

void MENU::mSet_Start(const SDL_DisplayMode * dsp)
{
	menu_start.setButtons(
	{
		{ { 100, 300, 100, 100 }, MENU_STATE::LC_MENU },
		{ { 200, 300, 100 , 100 }, MENU_STATE::MC_MENU },
	}
	);
}

void MENU::mSet_MC(const SDL_DisplayMode * dsp)
{
	menu_MC.setButtons(
	{
		
	}
	);
}

void MENU::mSet_LC(const SDL_DisplayMode * dsp)
{
	menu_LC.setButtons(
	{

	}
	);
}

void MENU::mSet_Pause(const SDL_DisplayMode * dsp)
{

}

void MENU::render(SDL_Renderer * rn)
{

}
