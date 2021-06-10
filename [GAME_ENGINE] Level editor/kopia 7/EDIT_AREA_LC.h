#pragma once
#include <SDL_render.h>
#include "EDIT_AREA_LC_state.h"

//class LevelCreator;

/// ==============================
//  Skrót EA - Edition Area
/// ==============================

class EDIT_AREA_LC
{
	//friend class LevelCreator; // zaprzyjaŸniona klasa
public:
	EDIT_AREA_LC() {}
	~EDIT_AREA_LC() {}

	void Init(const SDL_DisplayMode * dm, const int & scaleW, const int & scaleH);

	void events(SDL_Renderer * rn);

	EditArea_LC_state & getState() { return edit_state; }
private:
	void mouse_handler();

	void setPOS(const SDL_DisplayMode * dm, const int & scaleW, const int & scaleH);

	void render_ALL(SDL_Renderer * rn);
private:
	SDL_Rect position;
	EditArea_LC_state edit_state;
};

