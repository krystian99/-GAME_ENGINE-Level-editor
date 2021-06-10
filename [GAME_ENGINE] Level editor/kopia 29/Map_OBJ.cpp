#include "Map_OBJ.h"
#include "Mouse.h"
#include "Video_Info.h"
#include <cmath>

void Map_OBJ::set_mapPOS(const int & X, const int & Y)
{
	mapX = round(X * Video_Info::get_scaleW());
	mapY = round(Y * Video_Info::getWindow_H());
}
void Map_OBJ::events()
{
	Base_OBJ::events();
}
// tylko dane render_position.x i y - reszta ustalana przez obiekt pochodny: w i h
/*void Map_OBJ::setRenderPos(const int & render_X, const int & render_Y)
{
	render_position.x = round(render_X * Video_Info::getWindow_W());
	render_position.y = round(render_Y * Video_Info::getWindow_H());
}*/

/*void Map_OBJ::mouse_handler()
{
	int mX = Mouse::getX();
	int mY = Mouse::getY();

	clicked = false;

	if (mX >= render_position.x && mX <= render_position.x + render_position.w
		&& mY >= render_position.y && mY <= render_position.y + render_position.h)
	{
		if (Mouse::getBt_state() == Mouse_key::L_BUTTON && !clicked)
			clicked = true;
		else if (Mouse::getBt_state() == Mouse_key::NONE)
			clicked = false;
	}
}*/