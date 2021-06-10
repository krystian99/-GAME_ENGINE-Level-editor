#pragma once
#include <SDL_render.h>
#include "ScrollBar.h"

// v1 (29.02.2016) - rozpocz�to prac� nad obszarem edycji

class LevelCreator // odpowiada za generowanie w�a�ciwego kodu �r�d�owego, za umieszczanie obiekt�w na okre�lonych pozycjach
{
public:
	LevelCreator(const SDL_Rect & rt);

	void Init(const SDL_Rect & rt);

	void setPosition(const SDL_Rect & rt); // ustala pozycj� obszaru edycji poziomu

	void render(SDL_Renderer * rn);

	void mouse_handler(); // zdarzenia myszy
private:
	void Update_CodrinateBar(); // aktualizuje pozycj� myszki wzgl�dem textury levelu


private:
	SDL_Rect position; // obszar edycji

};

