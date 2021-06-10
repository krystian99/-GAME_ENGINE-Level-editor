#include "MENU.h"
#include "Video_Info.h"

void MENU::Init()
{
	mSet_Start();
}

void MENU::setRecentlyState()
{
	menu_state = recent_menu_state;
	MainAPP = recentAPP;
}

void MENU::render()
{
	switch (menu_state)
	{
	case MENU_STATE::START_MENU:
		menu_start.render();
		bt_input.render();
		break;
	}
}

void MENU::events()
{
	switch (menu_state)
	{
	case MENU_STATE::START_MENU:
		if (!bt_input.input_Is_empty()) {
			menu_start.events();
		}
		bt_input.events();
		break;
	}
}

void MENU::events_independent()
{
	switch (menu_state)
	{
	case MENU_STATE::START_MENU:
		menu_start.events_independent();
		break;
	}
}

void MENU::mSet_Start()
{
	int mid_screen_W = dsp->w / 2;
	int mid_screen_H = dsp->h / 2;

	SDL_Rect pos;

	int x, y, w, h;

	x = double(5) * scaleW;
	y = double(300) * scaleH;
	w = double(200) * scaleW;
	h = double(100) * scaleH;

	pos = { x, y, w, h };

	bt_input.Init(pos, "Map name", dsp, scaleW, scaleH);
	y += h + double(50) * scaleH;

	pos = { x, y, w, h };
	menu_start.addButton(MainAPP, menu_state, APP_state::IS_IN_LC, MENU_STATE::CREATING_LEVEL, recent_menu_state, recentAPP, pos, "NEW LEVEL");

	y += h + double(50) * scaleH;
	pos = { x, y, w, h };
	menu_start.addButton(MainAPP, menu_state, APP_state::IS_IN_LC, MENU_STATE::LOAD_LEVEL, recent_menu_state, recentAPP, pos, "LOAD LEVEL");

	menu_start.load_images("test.png");
}