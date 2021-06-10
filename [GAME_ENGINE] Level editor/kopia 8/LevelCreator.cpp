#include "LevelCreator.h"
#include "Mouse.h"
#include "Setup.h"
#include "Button_ChangeSB_resources.h"

LevelCreator::LevelCreator() :
	sbStatic{ ButtonType_LC::STATIC },
	sbDynamic{ ButtonType_LC::DYNAMIC },
	sbKey{ ButtonType_LC::KEY },
	cur_ScrollBar{ CurrentScrollBar::DYNAMIC },
	edition_area{},
	//button_movingMAP{ edition_area.getState(), EditArea_LC_state::MOVING_MAP },
	//button_selectingOBJ{ edition_area.getState(), EditArea_LC_state::SELECTING_OBJECT },
	DynamicCHNG{ cur_ScrollBar, CurrentScrollBar::DYNAMIC },
	StaticCHNG{ cur_ScrollBar, CurrentScrollBar::STATIC },
	KeyCHNG{ cur_ScrollBar, CurrentScrollBar::KEY },
	TEST_CHNG{ cur_ScrollBar, CurrentScrollBar::TEST }
{}

void LevelCreator::Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	edition_area.Init(dm, scaleW, scaleH);
	Init_ButtonsChangeSB(dm, scaleW, scaleH);
	ScrollBar::Init({ dm->w - int((100 * scaleW)), int(100 * scaleH), int(100 * scaleW), int(dm->h - (200 * scaleH)) }, scaleW, scaleH);
	Init_ScrollBars();
}

void LevelCreator::events(SDL_Renderer * rn)
{
	events_ScrollBar(rn);
	edition_area.events(rn);
	events_ButtonsChangeSB(rn);

	//Setup::PollEvents();
}

void LevelCreator::Init_ScrollBars()
{
	sbDynamic.InitButtons();
	sbKey.InitButtons();
	sbStatic.InitButtons();
}

void LevelCreator::Init_ButtonsChangeSB(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	SDL_Rect rt;
	int x, y, w, h;

	x = 5 * scaleW;
	w = 200 * scaleW;
	y = 5 * scaleH;
	h = 60 * scaleH;
	rt = { x, y, w ,h };
	DynamicCHNG.Init(rt);

	x += w;
	w = 160 * scaleW;
	rt = { x, y, w, h };
	StaticCHNG.Init(rt);

	x += w;
	w = 100 * scaleW;
	rt = { x, y, w, h };
	KeyCHNG.Init(rt);

	x += w;
	w = 100 * scaleW;
	rt = { x, y, w, h };
	TEST_CHNG.Init(rt);
	using namespace Button_ChangeSB_resources;

	DynamicCHNG.loadTX(Dynamic_backgroundTX);
	StaticCHNG.loadTX(Static_backgroundTX);
	KeyCHNG.loadTX(Key_backgroundTX);
	TEST_CHNG.loadTX(Dynamic_backgroundTX);

	DynamicCHNG.setRenderTEXT(TTF_path, "Dynamic", TTF_size, TTF_color);
	StaticCHNG.setRenderTEXT(TTF_path, "Static", TTF_size, TTF_color);
	KeyCHNG.setRenderTEXT(TTF_path, "Key", TTF_size, TTF_color);
	TEST_CHNG.setRenderTEXT(TTF_path, "TEST", TTF_size, TTF_color);
}

void LevelCreator::events_ScrollBar(SDL_Renderer * rn)
{
	switch (cur_ScrollBar)
	{
	case CurrentScrollBar::DYNAMIC:
		sbDynamic.events(rn);
		break;
	case CurrentScrollBar::STATIC:
		sbStatic.events(rn);
		break;
	case CurrentScrollBar::KEY:
		sbKey.events(rn);
		break;
	case CurrentScrollBar::TEST:
		//TEST.events(rn);
		break;
	}
}

/*void LevelCreator::events_EditArea(SDL_Renderer * rn)
{
	edition_area.events(rn);
}*/

void LevelCreator::events_ButtonsChangeSB(SDL_Renderer * rn)
{
	DynamicCHNG.events(rn);
	StaticCHNG.events(rn);
	KeyCHNG.events(rn);
	TEST_CHNG.events(rn);
}
