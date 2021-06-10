#include "MENU.h"

void MENU::setMenus(const SDL_DisplayMode * dsp)
{
	mSet_Start(dsp);
	mSet_LC(dsp);
	mSet_MC(dsp);
}

void MENU::events(SDL_Renderer * rn)
{
	switch (menu_state)
	{
	case MENU_STATE::START_MENU:
		menu_start.events(rn);
		break;
	case MENU_STATE::LC_MENU:
		menu_LC.events(rn);
		break;
	case MENU_STATE::MC_MENU:
		menu_MC.events(rn);
		break;
	case MENU_STATE::PAUSE_MENU:
		menu_pause.events(rn);
		break;
	}
}

void MENU::mSet_Start(const SDL_DisplayMode * dsp)
{
	int mid_screen_W = dsp->w / 2;
	int mid_screen_H = dsp->h / 2;
	menu_start.setButtons( 
		MainAPP, menu_state,
	{
		{ 
			{ 100, mid_screen_H - 100, mid_screen_W - 200, 100 }, MENU_STATE::LC_MENU, APP_state::IS_IN_MENU, "LevelCreator Menu"
		},
		{ 
			{ mid_screen_W + 100, mid_screen_H - 100, dsp->w - 100 - (mid_screen_W + 100), 100 }, MENU_STATE::MC_MENU, APP_state::IS_IN_MENU, "MenuCreator Menu"
		},
	}
	);
	// TEST
	menu_start.load_images("test.png");
	// END TEST
}

void MENU::mSet_MC(const SDL_DisplayMode * dsp)
{
	menu_MC.setButtons(
		MainAPP, menu_state,
	{
		{
			{ 100, 300, 100, 100 }, MENU_STATE::NONE, APP_state::IS_IN_MC, "NEW Menu"
		},
		{
			{ 300, 300, 100 , 100 }, MENU_STATE::MC_MENU, APP_state::IS_IN_MENU, "Load menu"
		},
	}
	);
	menu_MC.load_images("test.png");
}

void MENU::mSet_LC(const SDL_DisplayMode * dsp)
{
	int mid_screen_W = dsp->w / 2;
	int mid_screen_H = dsp->h / 2;

	menu_LC.setButtons(
		MainAPP, menu_state,
	{
		{
			{ 100, mid_screen_H - 100, mid_screen_W - 200, 100 }, MENU_STATE::NONE, APP_state::IS_IN_LC, "NEW LEVEL"
		},
		{
			{ mid_screen_W + 100, mid_screen_H - 100, dsp->w - 100 - (mid_screen_W + 100), 100 }, MENU_STATE::NONE, APP_state::IS_IN_MC, "LOAD LEVEL"
		},
	}
	);
	menu_LC.load_images("test.png");
}

void MENU::mSet_Pause(const SDL_DisplayMode * dsp)
{

}