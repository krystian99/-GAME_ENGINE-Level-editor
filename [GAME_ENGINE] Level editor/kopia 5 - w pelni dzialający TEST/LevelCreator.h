#pragma once
#include <SDL_render.h>
#include "ScrollBar.h"

// v1 (29.02.2016) - rozpoczêto pracê nad obszarem edycji

class LevelCreator // odpowiada za generowanie w³aœciwego kodu Ÿród³owego, za umieszczanie obiektów na okreœlonych pozycjach
{
public:
	LevelCreator(const SDL_Rect & rt);

	void Init(const SDL_Rect & rt);

	void setPosition(const SDL_Rect & rt); // ustala pozycjê obszaru edycji poziomu

	void render(SDL_Renderer * rn);

	void mouse_handler(); // zdarzenia myszy
private:
	void Update_CodrinateBar(); // aktualizuje pozycjê myszki wzglêdem textury levelu


private:
	SDL_Rect position; // obszar edycji

};

