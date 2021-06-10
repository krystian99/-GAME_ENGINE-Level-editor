#pragma once
#include "Button.h"
#include "Texture.h"
#include "OBJ_TYPES.h"

class Button_PlacingOBJ : public Button // klasa bazowa
{
public:
	Button_PlacingOBJ(const OBJ_TYPES &  type, const SDL_Rect & rt) :
		Button{ rt },
		obj_TYPE{ type },
		active{ false }
	{}

	Texture * getTexture_OBJ() { return texture; }

	const OBJ_TYPES & get_objType() const { return obj_TYPE; }

	virtual void render();
	virtual void events();

	virtual ~Button_PlacingOBJ() {}
protected:
	virtual void onClick();
	virtual void onMouseOver() = 0;
protected:
	Texture * texture;
private:
	bool active;
	OBJ_TYPES obj_TYPE;
};