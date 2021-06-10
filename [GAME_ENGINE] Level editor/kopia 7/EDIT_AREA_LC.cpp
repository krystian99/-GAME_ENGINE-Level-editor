#include "EDIT_AREA_LC.h"

void EDIT_AREA_LC::Init(const SDL_DisplayMode * dm, const int & scaleW, const int & scaleH)
{
	setPOS(dm, scaleW, scaleH); // ustala pozycjê
}

void EDIT_AREA_LC::events(SDL_Renderer * rn)
{
	switch (edit_state)
	{
	case EditArea_LC_state::SELECTING_OBJECT:
		break;
	case EditArea_LC_state::MOVING_OBJECT:
		break;
	case EditArea_LC_state::MOVING_MAP:
		break;
	default:
		break;
	}
}

void EDIT_AREA_LC::mouse_handler()
{

}

void EDIT_AREA_LC::setPOS(const SDL_DisplayMode * dm, const int & scaleW, const int & scaleH)
{
	int x = 20 * scaleW;
	int y = 50 * scaleH;
	int w = dm->w - (130 * scaleW) - x;
	int h = dm->h - (20 * scaleH) - y;

	position = { x, y, w, h };
}

void EDIT_AREA_LC::render_ALL(SDL_Renderer * rn)
{

}
