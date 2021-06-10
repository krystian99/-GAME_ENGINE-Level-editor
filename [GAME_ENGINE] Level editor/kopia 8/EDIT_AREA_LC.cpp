#include "EDIT_AREA_LC.h"
#include "Mouse.h"

void EDIT_AREA_LC::Init(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	setPOS(dm, scaleW, scaleH); // ustala pozycjê
}

void EDIT_AREA_LC::clearALL()
{

}

void EDIT_AREA_LC::events(SDL_Renderer * rn)
{
	render_ALL(rn);
}

void EDIT_AREA_LC::mouse_handler()
{
	if (Mouse::getMousePOSx() >= position.x && Mouse::getMousePOSx() <= position.x + position.w
		&& Mouse::getMousePOSy() >= position.y && Mouse::getMousePOSy() <= position.y + position.h)
	{
		if (edit_state == EditArea_LC_state::MOVING_OBJECT) {
			if (Mouse::get_lButton_State())
				; // po³ó¿ obiekt wzglêdem obszaru edycji
			else if (Mouse::get_rButton_State())
				; // przerzuæ obiekt poziomo
		}
	}
}

void EDIT_AREA_LC::setPOS(const SDL_DisplayMode * dm, const double & scaleW, const double & scaleH)
{
	int x = 20 * scaleW;
	int y = 80 * scaleH;
	int w = dm->w - (130 * scaleW) - x;
	int h = dm->h - (80 * scaleH) - y;

	position = { x, y, w, h };
}

void EDIT_AREA_LC::render_ALL(SDL_Renderer * rn)
{
	SDL_SetRenderDrawColor(rn, 255, 0, 0, 255);
	SDL_RenderDrawRect(rn, &position);
	SDL_SetRenderDrawColor(rn, 255, 255, 255, 255);
}
