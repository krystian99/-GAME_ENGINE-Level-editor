#include "Map_mouseHandler.h"
#include "Mouse.h"
#include "CoordinateBar_map.h"

void Map_mouseHandler::events(bool mouse_over)
{
	//if (mouse_over && Mouse::isUpdated())
	//{
		// przycisk klikniêty w danym miejscu
		if (Mouse::getBt_state() == Mouse_key::L_BUTTON)
			clicked_point.set(CoordinateBar_map::getX(), CoordinateBar_map::getY());

	//}
}
