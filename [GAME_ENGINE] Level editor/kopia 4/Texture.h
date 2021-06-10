#pragma once
#include <string>
#include <SDL_render.h>

class Texture
{
public:
	Texture() : mTexture{ nullptr }, mWidth{ 0 }, mHeight{ 0 } {}
	~Texture();
	bool loadFromFile(std::string path);

	void render(SDL_Renderer * rn, const SDL_Rect * src, const SDL_Rect * dst, SDL_RendererFlip = SDL_FLIP_NONE);

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

