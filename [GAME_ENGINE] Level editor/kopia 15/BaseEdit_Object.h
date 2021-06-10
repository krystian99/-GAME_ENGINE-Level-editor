#pragma once
#include <SDL_rect.h>
#include <vector>
#include <memory>

using std::vector;

class BaseEdit_Object
{
public:
	BaseEdit_Object();
	void setPOS(SDL_Rect * rt);

	~BaseEdit_Object();
private:
	std::unique_ptr<int> Player;
	int scaleX, scaleY;
	int posX, posY;

	int Width, Height;
};

