#include "Button_PlacingOBJ.h"

void Button_PlacingOBJ::render()
{
	Button::render();
	texture->render(nullptr, &position);
}

void Button_PlacingOBJ::events()
{
	//if (!active)
		Button::events();
}

void Button_PlacingOBJ::onClick()
{
	active = true;
	//LevelEditor_manager::setPlacing_state(obj_TYPE, getTexture_OBJ());
}