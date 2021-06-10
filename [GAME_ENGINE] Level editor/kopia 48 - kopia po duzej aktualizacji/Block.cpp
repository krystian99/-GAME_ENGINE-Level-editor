#include "Block.h"
#include "Mouse.h"

void Block::events()
{
	updateEvent();
	mouse_handler();
}

void Block::set_renderPOS(int x, int y, int w, int h)
{
	renderPOS = { x, y, w, h };
}

void Block::set_mapPOS(int x, int y, int w, int h)
{
	mapPOS = { x, y, w, h };
}

void Block::update_renderPOS(int x, int y)
{
	renderPOS.x = x;
	renderPOS.y = y;
}

void Block::update_mapPOS(int x, int y)
{
	mapPOS.x = x;
	mapPOS.y = y;
}

void Block::mouse_handler()
{
	if (Mouse::getX() >= renderPOS.x && Mouse::getX() <= renderPOS.x + renderPOS.w
		&& Mouse::getY() >= renderPOS.y && Mouse::getY() <= renderPOS.y + renderPOS.h)
	{
		if (Mouse::getBt_state() != Mouse_key::NONE) // czy klikniêto raz middle Mouse
		{
			switch (Mouse::getBt_state()) {
			case Mouse_key::MID_BUTTON:

				break;
			case Mouse_key::L_BUTTON:

				break;
			case Mouse_key::R_BUTTON:

				break;
			}
		}
	}
}

void Block::updateEvent()
{
	middleM_pressed = false;
	leftM_pressed = false;
	rightM_pressed = false;
}