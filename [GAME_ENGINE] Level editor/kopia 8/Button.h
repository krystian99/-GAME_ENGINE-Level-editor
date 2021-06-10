#pragma once
#include "Texture.h"
#include <string>
#include <SDL_events.h>
#include "Menu_State.h"
#include "APP_State.h"

enum class Button_State { SELECTED, UNSELECTED };

class Button
{
public:
	Button() : 
		bt_state{ Button_State::UNSELECTED }
	{}

	bool is_clicked() const { return clicked; } // przydatna metoda

	void Init(const SDL_Rect & rt);

	void setPosition(const SDL_Rect & rt);

	const SDL_Rect * getPOS() const { return &position; } // zhermetyzowane dane - lepsza czytelnoœæ, mniej b³êdów

	void mouse_handler();

	void setState(const Button_State & stateToChange);

	const int & getTX_Width() const { return tX.getWidth(); }
	const int & getTX_Height() const { return tX.getHeight(); }

	//const int & getWidth() const { return Width; }
	//const int & getHeight() const { return Height; }

	void loadTX(std::string path);

	virtual ~Button() {}
protected:
	Texture tX;
protected:
	void render(SDL_Renderer * rn);

	virtual void onClick() = 0; // metoda czysto-wirtualna
	virtual void onMouseOver() = 0;
private:
	bool clicked;

	Button_State bt_state;

	SDL_Rect position;

	int Width;
	int Height;
};

