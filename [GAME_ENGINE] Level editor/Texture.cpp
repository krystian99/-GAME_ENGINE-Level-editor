#include <SDL_image.h>
#include "Texture.h"
#include "Error.h"
#include "Renderer.h"
#include <SDL_ttf.h>

Texture::~Texture()
{
	free();
}

void Texture::loadFromFile(const std::string & path)
{
	free();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;

	if (!(loadedSurface = IMG_Load(path.c_str())))
		throw Error::throw_Message({IMG_GetError() });

	//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(Renderer::get(), loadedSurface);
	if (!newTexture)
		throw Error::throw_Message({ SDL_GetError() });

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	//texture_loaded = true;

	SDL_FreeSurface(loadedSurface);
	mTexture = newTexture;

	SDL_GetTextureColorMod(mTexture, &defualut_color_mod.r, &defualut_color_mod.g, &defualut_color_mod.b);
}

void Texture::loadFromFile(SDL_Renderer * rn, const std::string & path)
{
	free();
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;

	if (!(loadedSurface = IMG_Load(path.c_str())))
		throw Error::throw_Message({ IMG_GetError() });

	//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(rn, loadedSurface);
	if (!newTexture)
		throw Error::throw_Message({ SDL_GetError() });

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	//texture_loaded = true;

	SDL_FreeSurface(loadedSurface);
	mTexture = newTexture;

	SDL_GetTextureColorMod(mTexture, &defualut_color_mod.r, &defualut_color_mod.g, &defualut_color_mod.b);
}

void Texture::loadFromText(const std::string & render_text, TTF_Font * font, SDL_Color color)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, render_text.c_str(), color);
	if (textSurface == nullptr)
		throw Error::throw_Message("Unable to render text surface! SDL_ttf Error: \n" + std::string{ TTF_GetError() });

	//Create texture from surface pixels
	else if (!(mTexture = SDL_CreateTextureFromSurface(Renderer::get(), textSurface)))
		throw Error::throw_Message("Unable to create texture from rendered text! SDL Error: \n" + std::string{ SDL_GetError() });

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	//texture_loaded = true;

	SDL_GetTextureColorMod(mTexture, &defualut_color_mod.r, &defualut_color_mod.g, &defualut_color_mod.b);

	SDL_FreeSurface(textSurface);
}

void Texture::loadFromText(SDL_Renderer * rn, const std::string & render_text, TTF_Font * font, SDL_Color color)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, render_text.c_str(), color);
	if (textSurface == nullptr)
		throw Error::throw_Message("Unable to render text surface! SDL_ttf Error: \n" + std::string{ TTF_GetError() });

	//Create texture from surface pixels
	else if (!(mTexture = SDL_CreateTextureFromSurface(rn, textSurface)))
		throw Error::throw_Message("Unable to create texture from rendered text! SDL Error: \n" + std::string{ SDL_GetError() });

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	//texture_loaded = true;

	SDL_GetTextureColorMod(mTexture, &defualut_color_mod.r, &defualut_color_mod.g, &defualut_color_mod.b);

	SDL_FreeSurface(textSurface);
}

void Texture::modulate_color(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::reset_colorModulation()
{
	SDL_SetTextureColorMod(mTexture, defualut_color_mod.r, defualut_color_mod.g, defualut_color_mod.b);
}

void Texture::set_blendAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(mTexture, a);
}

void Texture::set_rotate_angle(int x)
{
	rotate_angle = x;
}

void Texture::render(const SDL_Rect * src, const SDL_Rect * dst, SDL_RendererFlip flip)
{
	//if (is_loaded())
		SDL_RenderCopyEx(Renderer::get(), mTexture, src, dst, 0, nullptr, flip);
}

void Texture::render(SDL_Renderer * rn, const SDL_Rect * src, const SDL_Rect * dst, SDL_RendererFlip flip)
{
	//if (is_loaded())
		SDL_RenderCopyEx(rn, mTexture, src, dst, 0, nullptr, flip);
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

