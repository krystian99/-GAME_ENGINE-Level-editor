#pragma once
#include "Texture.h"
#include <string>
#include <SDL_events.h>

enum class ButtonType : char { STATIC, DYNAMIC, KEY };

class Button
{
public:
	Button(std::string(*point)(int x, int y), std::string pathTX);
	Button() : position{}, tX{}, pointer{} {}

	void generateCode() const;

	void onClick();

	bool is_clicked() const { return clicked; }

	void setPosition(const SDL_Rect & rt );

	const SDL_Rect * getPOS() const { return &position; }

	void render(SDL_Renderer * rn, SDL_Rect * rt = nullptr, SDL_RendererFlip = SDL_FLIP_NONE);

	void mouse_handler();

	static const int & getWidth() { return Width; }
	static const int & getHeight() { return Height; }

	void loadTX(std::string path);

	~Button() {};
private:
	bool clicked;

	static const int Width = 90;
	static const int Height = 90;

	SDL_Rect position;

	std::string(*pointer)(int x, int y);

	Texture tX;
};

