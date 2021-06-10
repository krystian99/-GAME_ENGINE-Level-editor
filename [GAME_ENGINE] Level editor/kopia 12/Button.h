#pragma once
#include "Texture.h"
#include <string>
#include <SDL_events.h>

enum class Button_State { SELECTED, UNSELECTED };

class Button
{
public:
	Button() : 
		bt_state{ Button_State::UNSELECTED },
		clicked{ false }, l_bt_pressing{ false }
	{}

	bool is_clicked() const { return clicked; } // przydatna metoda

	void Init(const SDL_Rect & rt);

	void setPosition(const SDL_Rect & rt);

	const SDL_Rect * getPOS() const { return &position; } // zhermetyzowane dane - lepsza czytelnoœæ, mniej b³êdów

	void mouse_handler();

	void setState(const Button_State & stateToChange);

	const Button_State & getState() const { return bt_state; }

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

	bool l_bt_pressing;
	Button_State bt_state;

	SDL_Rect position;

	//Texture tX;

	int Width;
	int Height;
};

