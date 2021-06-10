#pragma once
#include "Button.h"
#include <string>

enum class ButtonType_LC { DYNAMIC, STATIC, KEY };

enum class ButtonLC_state { SELECTED, UNSELECTED };

class Button_LC : public Button
{
public:
	Button_LC();

	//void render(SDL_Renderer * rn, SDL_Rect * rt = nullptr);
	void render(SDL_Renderer * rn); // renderuj ca³oœæ
	void render(SDL_Renderer * rn, int startX, int startY, SDL_Rect * clip);

	~Button_LC();
private:
	virtual void onClick();
	virtual void onMouseOver();
};

