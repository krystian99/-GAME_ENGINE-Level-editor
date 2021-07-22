#include "Map_moveMouse_module.h"
#include "Mouse.h"

void Map_moveMouse_module::events()
{
	Object::events();
}

void Map_moveMouse_module::on_mouseL_press()
{
	static double scaleX, scale_recentX;
	static double scaleY, scale_recentY;

	static int pointX, point_recentX;

	static int maprender_absX, maprender_absY;

	if (Mouse::moved()) {

		scaleX = double(Mouse::getX() - edit_area.left()) / double(edit_area.getW());
		scale_recentX = double(Mouse::getR_x() - edit_area.left()) / double(edit_area.getW());

		pointX = mapBG_area.left() + round(mapBG_area.getW() * scaleX);
		point_recentX = mapBG_area.left() + round(mapBG_area.getW() * scale_recentX);

		maprender_absX = abs(pointX - point_recentX);

		if (Mouse::getX() < Mouse::getR_x() && mapBG_area.right() < mapBG.getWidth()) {
			if (mapBG_area.right() + maprender_absX < mapBG.getWidth())
				mapBG_area.update_position(maprender_absX, 0);
			else
				mapBG_area.setX(mapBG.getWidth() - mapBG_area.getW());
		}
		else if (Mouse::getX() > Mouse::getR_x() && mapBG_area.left() > 0) {

			if (mapBG_area.left() - maprender_absX > 0)
				mapBG_area.updateX(-maprender_absX);
			else
				mapBG_area.setX(0);
		}

		for (auto& enemy : enemies)
			enemy->set_renderPOS(edit_area, mapBG_area);
	}
}
