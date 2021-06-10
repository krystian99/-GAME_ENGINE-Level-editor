#include <SDL_image.h>
#include "Texture.h"
#include "Exceptions.h"
#include "Setup.h"

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(std::string path)
{
	free();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;

	if (!(loadedSurface = IMG_Load(path.c_str())))
		throw Error{ IMG_GetError() };

	//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(Setup::getRenderer(), loadedSurface);
	if (!newTexture)
		throw Error{ SDL_GetError() };

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface); // zwolnienie zasobów zmienn¹ tymczasow¹
	mTexture = newTexture;

	return mTexture != nullptr;
}

void Texture::loadFromText(std::string render_text, TTF_Font * font, SDL_Color color)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, render_text.c_str(), color);
	if (textSurface == nullptr)
		throw Error{ "Unable to render text surface! SDL_ttf Error: \n" + std::string{ TTF_GetError() } };

	//Create texture from surface pixels
	else if (!(mTexture = SDL_CreateTextureFromSurface(Setup::getRenderer(), textSurface)))
		throw Error{ "Unable to create texture from rendered text! SDL Error: \n" + std::string{ SDL_GetError() } };

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	//Get rid of old surface
	SDL_FreeSurface(textSurface);
}

void Texture::render(SDL_Renderer * rn, const SDL_Rect * src, const SDL_Rect * dst, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(rn, mTexture, src, dst, 0, nullptr, flip);
	//SDL_RenderCopy(rn, mTexture, nullptr, dst);
}

void Texture::free()
{
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

