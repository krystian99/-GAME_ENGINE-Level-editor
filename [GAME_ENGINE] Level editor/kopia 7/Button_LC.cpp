#include "Button_LC.h"



Button_LC::Button_LC()
{

}


/*void Button_LC::render(SDL_Renderer * rn, SDL_Rect * rt)
{
	const SDL_Rect * pos = getPOS();
	if (rt) { // renderuj czêœæ textury
		double scaleX = double(tX.getWidth()) / double(getWidth()); // skalowanie rozmiaru
		double scaleY = double(tX.getHeight()) / double(getHeight()); // skalowanie rozmiaru

		int y = tX.getHeight() - (rt->h * scaleY);
		int h = tX.getHeight() - y;

		int x = tX.getWidth() - (rt->w * scaleX);
		int w = tX.getWidth() - x;

		SDL_Rect clip = { x, y, w, h };
		tX.render(rn, &clip, rt);
		SDL_RenderDrawRect(rn, rt);
	}
	else { // renderuj ca³¹ texturê
		tX.render(rn, nullptr, pos);
		SDL_RenderDrawRect(rn, pos);
	}
}*/

void Button_LC::render(SDL_Renderer * rn)
{
	tX.render(rn, nullptr, getPOS());
	SDL_RenderDrawRect(rn, getPOS());
}

void Button_LC::render(SDL_Renderer * rn, int startX, int startY, SDL_Rect * clip)
{
	SDL_Rect area = { startX, startY, tX.getWidth() - startX, tX.getHeight() - startY };
	tX.render(rn, &area, clip);
	SDL_RenderDrawRect(rn, clip);
}

Button_LC::~Button_LC()
{
}

void Button_LC::onClick()
{

}
