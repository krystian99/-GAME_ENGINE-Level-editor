#pragma once
#include <string>
#include <SDL_render.h>
#include <SDL_ttf.h>

class Texture
{
public:
	Texture() :
		mTexture{ nullptr }, mWidth{ 0 }, mHeight{ 0 }, texture_loaded{ false } 
	{}
	Texture(const char * str) : 
		Texture{}
	{
		loadFromFile(str);
	}
	~Texture();

	void loadFromFile(const std::string & path);
	void loadFromFile(SDL_Renderer * rn, const std::string & path);
	void loadFromText(const std::string & path, TTF_Font * font, SDL_Color color);
	void loadFromText(SDL_Renderer * rn, const std::string & path, TTF_Font * font, SDL_Color color);

	SDL_Texture * get() { return mTexture; }

	void modulate_color(Uint8 red, Uint8 green, Uint8 blue);
	void set_blendAlpha(Uint8 a);

	const bool & is_loaded() const { return texture_loaded; }

	void render(const SDL_Rect * src, const SDL_Rect * dst, SDL_RendererFlip = SDL_FLIP_NONE); // renderuj w g³ównym oknie
	void render(SDL_Renderer * rn, const SDL_Rect * src, const SDL_Rect * dst, SDL_RendererFlip = SDL_FLIP_NONE);

	const int & getWidth() const { return mWidth; }
	const int & getHeight() const { return mHeight; }
private:
	void free();
private:
	bool texture_loaded;

	SDL_Texture * mTexture;

	// Wymiary textury 
	int mWidth;
	int mHeight;
};

