#include "LevelCreator.h"
#include "Mouse.h"
#include "Exceptions.h"
#include "Setup.h"

LevelCreator::LevelCreator() :
	sbStatic{ ButtonType_LC::STATIC, SB_Orientation::VERTICAL },
	sbDynamic{ ButtonType_LC::DYNAMIC, SB_Orientation::VERTICAL },
	sbKey{ ButtonType_LC::KEY, SB_Orientation::HORIZONTAL },
	cur_ScrollBar{ CurrentScrollBar::DYNAMIC },
	edition_area{},
	button_movingMAP{ edition_area.getState(), EditArea_LC_state::MOVING_MAP },
	button_selectingOBJ{ edition_area.getState(), EditArea_LC_state::SELECTING_OBJECT }
{}

void LevelCreator::Init(const SDL_DisplayMode * dm, const int & scaleW, const int & scaleH)
{
	edition_area.Init(dm, scaleW, scaleH);
	sbStatic.Init({ 0, 100 * scaleH, 100 * scaleW, dm->h - (200 * scaleH) });
	sbDynamic.Init({ dm->w - (100 * scaleW), 100 * scaleH, 100 * scaleW, dm->h - (200 * scaleH) });
	sbKey.Init({ 100 * scaleW , 0, dm->w - (200 * scaleW), 100 * scaleW });
}

void LevelCreator::events(SDL_Renderer * rn)
{
	switch_events();

	events_ScrollBars(rn);
	events_EditArea(rn);

	Setup::PollEvents();
}

void LevelCreator::switch_events()
{
	switch (stateLC)
	{
	case LevelCreator_state::Generating_CODE:
		break;
	}
}

void LevelCreator::Init_ScrollBars()
{

}

void LevelCreator::Init_IndependentButtons()
{

}

void LevelCreator::events_ScrollBars(SDL_Renderer * rn)
{
	sbStatic.events(rn);
	sbDynamic.events(rn);
	sbKey.events(rn);
}

void LevelCreator::events_EditArea(SDL_Renderer * rn)
{

}