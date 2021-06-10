#pragma once
#include "Texture.h"
#include <string>
#include <SDL_events.h>

enum class ButtonType : char {
	LC, // LC - Level Creator
	MC // MC - Menu Creator
};

class Button
{
public:
	Button(){}
	Button(const int & w, const int & h) : Width{ w }, Height{ h } {}

	virtual void onClick() = 0;

	bool is_clicked() const { return clicked; }

	void setPosition(const SDL_Rect & rt );

	const SDL_Rect * getPOS() const { return &position; }

	void render(SDL_Renderer * rn, SDL_Rect * rt = nullptr, SDL_RendererFlip = SDL_FLIP_NONE);

	virtual void mouse_handler();

	const int & getWidth() const { return Width; }
	const int & getHeight() const { return Height; }

	void loadTX(std::string path);

	virtual ~Button() = 0;
private:
	bool clicked;

	int Width;
	int Height;

	SDL_Rect position;

	Texture tX;
};

