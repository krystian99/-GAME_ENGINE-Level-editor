#pragma once
#include <string>
#include <SDL_render.h>
#include "Font.h"
#include "Button.h"

class Button_TEXT : public Button
{
public:
	Button_TEXT() {}
	~Button_TEXT() {}

	//void setPOS_TEXT(const SDL_Rect & rt);

	void setRenderTEXT(std::string ttf_path, std::string renderedText, int height, SDL_Color color);
protected:
	virtual void onClick() = 0;
	virtual void onMouseOver() = 0;
protected:
	static const int FRAME_SIZE = 10; // wyznacza odleg³oœæ renderowania tekstu od pocz¹tku koordynatów x lub y

	Font text;
	SDL_Rect textPOS;
};

