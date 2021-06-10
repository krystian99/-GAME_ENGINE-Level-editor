#pragma once
#include <string>
#include <SDL_render.h>
#include <SDL_ttf.h>

class Texture
{
public:
	Texture() : mTexture{ nullptr }, mWidth{ 0 }, mHeight{ 0 } {}
	~Texture();

	void loadFromFile(const std::string & path);
	void loadFromText(const std::string & path, TTF_Font * font, SDL_Color color);

	SDL_Texture * get() { return mTexture; }

	void render(const SDL_Rect * src, const SDL_Rect * dst, SDL_RendererFlip = SDL_FLIP_NONE);

	const int & getWidth() const { return mWidth; }
	const int & getHeight() const { return mHeight; }
private:
	void free();
private:
	SDL_Texture * mTexture;

	// Wymiary textury 
	int mWidth;
	int mHeight;
};

